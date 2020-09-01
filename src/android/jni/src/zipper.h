#include <string>

int compress(int overwrite, int exclude, const std::string& inputdir, const std::string& output_filename);
int uncompress(int overwrite, const char* archive, const char* outputdir);