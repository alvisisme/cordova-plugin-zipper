// global cordova, module
module.exports = {
    /**
     * 压缩文件列表为zip包
     * @param {Object} options 压缩参数
     * @param {Number} options.overwrite （可选）压缩时是否覆盖原有文件，0表示不覆盖，1表示覆盖，默认值为0不覆盖
     * @param {Number} options.zipfile  压缩后产生的压缩包路径
     * @param {String} options.file 需要加入压缩包的文件或者目录路径
     * 
     * @param {Function} successCallback 
     * @param {Function} errorCallback 
     * 
     * @example
     *    <code>
     *      const options = {
     *          overwrite: 1,
	 *          zipfile: '/sdcard/templates.zip',
	 *          file: '/sdcard/dir/test.json'
     *      }
     *      cordova.plugins.zipper.compress(options, function () {
     *          console.log('success')
     *      }, function (error) {
     *          console.log(error)
     *      })
     *    </code>
     */
    compress: function (options, successCallback, errorCallback) {
        const opt =  {
            overwrite: 0, 
            exclude: 1
        };
        if (typeof options.overwrite === 'number') {
            if (options.overwrite === 1 || options.overwrite === 0) {
                opt.overwrite = options.overwrite;
            }
        }
        // TODO: 暂不可用
        // @param {Number} options.exclude （可选）当options.file为目录时，压缩时是否保留最内层的目录，如 /sdcard/test/，1表示不保留，压缩包不包含test目录，0表示保留，压缩包包含test目录，默认为1不保留
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
     * @param {Object} options 解压参数
     * @param {Number} options.overwrite （可选）解压时是否覆盖原有文件，0表示不覆盖，1表示覆盖， 默认值为1覆盖
     * @param {Number} options.zipfile  需要解压的zip文件路径
     * @param {String} options.targetpath 解压后文件的存放路径，需要确保该目录存在，否则返回错误
     * 
     * @param {Function} successCallback 
     * @param {Function} errorCallback 
     * 
     * @example
     *   <code>
     *      const options = {
     *          overwrite: 1,
	 *          zipfile: '/sdcard/templates.zip',
	 *          targetpath: '/sdcard'
     *      }
     *      cordova.plugins.zipper.uncompress(options, function () {
     *          console.log('success')
     *      }, function (error) {
     *          console.log(error)
     *      })
     *   </code>
     */
    uncompress: function (options, successCallback, errorCallback) {
        const opt =  {
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
    }
};
