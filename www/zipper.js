// global cordova, module

/**
 * 调用成功回调函数
 * 
 * @callback successCallback
 */

/**
 * 调用错误回调函数
 * 
 * @callback errorCallback
 * @param {String} reason 错误原因
 */

/**
 * @module cordova.plugins.zipper
 */
module.exports = {
  /**
   * 压缩文件列表为zip包
   * 
   * @param {Object} options 压缩参数
   * @param {String} options.file 需要加入压缩包的文件或者目录路径
   * @param {String} options.zipfile 压缩后产生的压缩包路径
   * 
   * @param {successCallback} successCallback 成功回调
   * @param {errorCallback} errorCallback 错误回调
   * 
   * @example
   * const options = {
   *   file: '/sdcard/dir/test.json'，
   *   zipfile: '/sdcard/templates.zip'
   * }
   * cordova.plugins.zipper.compress(options, function () {
   *   console.log('success')
   * }, function (error) {
   *   console.log(error)
   * })
   */
  compress: function (options, successCallback, errorCallback) {
    const opt = {
      overwrite: 0,
      exclude: 1
    };
    if (typeof options.overwrite === 'number') {
      if (options.overwrite === 1 || options.overwrite === 0) {
        opt.overwrite = options.overwrite;
      }
    }
    if (typeof options.exclude === 'number') {
      if (options.exclude === 1 || options.exclude === 0) {
        opt.exclude = options.exclude;
      }
    }
    opt.zipfile = options.zipfile;
    opt.file = options.file;

    const args = [];
    args.push(opt.overwrite)
    args.push(opt.exclude)
    args.push(opt.zipfile)
    args.push(opt.file)
    cordova.exec(successCallback, errorCallback, "Zipper", "compress", args);
  },
  /**
   * 解压zip包
   * 
   * @param {Object} options 解压参数
   * @param {String} options.zipfile  需要解压的zip文件路径
   * @param {String} options.targetpath 解压后文件的存放路径，需要确保该目录存在，否则返回错误
   * 
   * @param {successCallback} successCallback 成功回调
   * @param {errorCallback} errorCallback 错误回调
   * 
   * @example
   * const options = {
   *   zipfile: '/sdcard/templates.zip',
   *   targetpath: '/sdcard'
   * }
   * cordova.plugins.zipper.uncompress(options, function () {
   *   console.log('success')
   * }, function (error) {
   *   console.log(error)
   * })
   */
  uncompress: function (options, successCallback, errorCallback) {
    const opt = {
      overwrite: 1
    };
    if (typeof options.overwrite === 'number' && options.overwrite === 0) {
      opt.overwrite = options.overwrite;
    }
    opt.zipfile = options.zipfile;
    opt.targetpath = options.targetpath;

    const args = [];
    args.push(opt.overwrite);
    args.push(opt.zipfile);
    args.push(opt.targetpath);
    cordova.exec(successCallback, errorCallback, "Zipper", "uncompress", args);
  },
};
