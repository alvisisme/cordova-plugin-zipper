#include "zipper.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <iostream>
#include <string>

#include <zip.h>
#include "log.h"

static int safe_create_dir(const char *dir)
{
    if (mkdir(dir, 0755) < 0) {
        if (errno != EEXIST) {
            perror(dir);
            return 1;
        }
    }
    return 0;
}

static bool is_dir(const std::string& dir)
{
  struct stat st;
  ::stat(dir.c_str(), &st);
  return S_ISDIR(st.st_mode);
}

static bool is_file(const std::string& file)
{
  struct stat st;
  ::stat(file.c_str(), &st);
  return S_ISREG(st.st_mode);
}

static void walk_directory(const std::string& startdir, const std::string& inputdir, zip_t *zipper)
{
  DIR *dp = ::opendir(inputdir.c_str());
  if (dp == nullptr) {
    throw std::runtime_error("Failed to open input directory: " + std::string(::strerror(errno)));
  }

  struct dirent *dirp;
  while ((dirp = readdir(dp)) != NULL) {
    if (dirp->d_name != std::string(".") && dirp->d_name != std::string("..")) {
      std::string fullname = inputdir + "/" + dirp->d_name;
      if (is_dir(fullname)) {
        if (zip_dir_add(zipper, fullname.substr(startdir.length() + 1).c_str(), ZIP_FL_ENC_UTF_8) < 0) {
          LOGE("%s %d: Failed to add directory to zip:  %s", __FILE__, __LINE__, zip_strerror(zipper));
          throw std::runtime_error("Failed to add directory to zip: " + std::string(zip_strerror(zipper)));
        }
        walk_directory(startdir, fullname, zipper);
      } else {
        zip_source_t *source = zip_source_file(zipper, fullname.c_str(), 0, 0);
        if (source == nullptr) {
          LOGE("%s %d: Failed to add file to zip:  %s", __FILE__, __LINE__, zip_strerror(zipper));
          throw std::runtime_error("Failed to add file to zip: " + std::string(zip_strerror(zipper)));
        }
        if (zip_file_add(zipper, fullname.substr(startdir.length() + 1).c_str(), source, ZIP_FL_ENC_UTF_8) < 0) {
          zip_source_free(source);
          LOGE("%s %d: Failed to add file to zip:  %s", __FILE__, __LINE__, zip_strerror(zipper));
          throw std::runtime_error("Failed to add file to zip: " + std::string(zip_strerror(zipper)));
        }
      }
    }
  }
  ::closedir(dp);
}

static void zip_file(const std::string& fullname, zip_t *zipper) {
  zip_source_t *source = zip_source_file(zipper, fullname.c_str(), 0, 0);
  if (source == nullptr) {
    LOGE("%s %d: Failed to add file to zip:  %s", __FILE__, __LINE__, zip_strerror(zipper));
    throw std::runtime_error("Failed to add file to zip: " + std::string(zip_strerror(zipper)));
  }

  std::string::size_type pos = fullname.find_last_of('/') + 1;
  std::string filename = fullname.substr(pos, fullname.length() - pos);

  if (zip_file_add(zipper, filename.c_str(), source, ZIP_FL_ENC_UTF_8) < 0) {
    zip_source_free(source);
    LOGE("%s %d: Failed to add file to zip:  %s", __FILE__, __LINE__, zip_strerror(zipper));
    throw std::runtime_error("Failed to add file to zip: " + std::string(zip_strerror(zipper)));
  }
}

int compress(int overwrite, int exclude, const std::string& inputdir, const std::string& output_filename)
{  
  int errorp;
  zip_t *zipper = zip_open(output_filename.c_str(), ZIP_CREATE | ZIP_TRUNCATE, &errorp);
  if (zipper == nullptr) {
    zip_error_t ziperror;
    zip_error_init_with_code(&ziperror, errorp);
    LOGE("%s %d: Failed to open output file %s : %s" , __FILE__, __LINE__, output_filename.c_str(), zip_error_strerror(&ziperror));
    return 10001;
  }

  LOGD("%s %d: compressing dir %s", __FILE__, __LINE__, inputdir.c_str());
  // std::string::size_type pos = inputdir.find_last_of('/') + 1;
  // std::string dirname = inputdir.substr(pos, inputdir.length() - pos);
  if (is_file(inputdir)) {
    try {
      zip_file(inputdir, zipper);
    } catch(...) {
      LOGE("%s %d: compressing file error %s", __FILE__, __LINE__);
      zip_close(zipper);
      return -1;
    }
  } else {
    try {
      walk_directory(inputdir, inputdir, zipper);
    } catch(...) {
      LOGE("%s %d: compressing dir error %s", __FILE__, __LINE__);
      zip_close(zipper);
      return -1;
    }
  }
  zip_close(zipper);
  return 0;
}

int uncompress(int overwrite, const char* archive, const char* outputdir)
{
    struct zip *za;
    struct zip_file *zf;
    struct zip_stat sb;
    char buf[100];
    int err;
    int i, len;
    int fd;
    long long sum;

    if ((za = zip_open(archive, 0, &err)) == NULL) {
        zip_error_to_str(buf, sizeof(buf), err, errno);
        LOGE("can't open zip archive `%s': %s\n", archive, buf);
        return 1;
    }
    
    for (i = 0; i < zip_get_num_entries(za, 0); i++) {
        if (zip_stat_index(za, i, 0, &sb) == 0) {
            len = strlen(sb.name);
            std::string outputPath = std::string(outputdir) + std::string("/") +std::string(sb.name);
            if (!overwrite && (access(outputPath.c_str(), F_OK) != -1)) {
              LOGE("%s:%d %s exists but overwrite flag is not set\n", __FILE__, __LINE__, outputPath.c_str());
              return 1000;
            }
            if (sb.name[len - 1] == '/') {
                int res = safe_create_dir(outputPath.c_str());
                if (res != 0) {
                  return res;
                }
            } else {
                zf = zip_fopen_index(za, i, 0);
                if (!zf) {
                    LOGE("%s:%d zip_fopen_index error\n", __FILE__, __LINE__);
                    return 100;
                }
                fd = open(outputPath.c_str(), O_RDWR | O_TRUNC | O_CREAT, 0644);
                LOGD("%s:%d outputPath %s %d\n", __FILE__, __LINE__, outputPath.c_str(), fd);
                if (fd < 0) {
                    LOGE("%s:%d open %s error \n", __FILE__, __LINE__, sb.name);
                    return 101;
                }
 
                sum = 0;
                while (sum != sb.size) {
                    len = zip_fread(zf, buf, 100);
                    if (len < 0) {
                        LOGE("%s:%d zip_fread error\n", __FILE__, __LINE__);
                        return 102;
                    }
                    write(fd, buf, len);
                    sum += len;
                }
                close(fd);
                zip_fclose(zf);
            }
        } else {
          LOGI("File[%s] Line[%d]\n", __FILE__, __LINE__);
        }
    }

    if (zip_close(za) == -1) {
        LOGE("can't close zip archive `%s'\n", archive);
        return 1;
    }
    return 0;
}
