# Cordova Zipper Plugin

一个zip压缩与解压插件。

## 如何使用

1. 创建一个cordova工程

    ```bash
    cordova create cordova-test-app 
    cd cordova-test-app
    ```

2. 安装插件

    通过git仓库方式安装

    ```bash
    cordova plugin add git+https://github.com/alvisisme/cordova-plugin-zipper.git
    ```

    通过本地文件方式安装

    ```bash
    git clone https://github.com/alvisisme/cordova-plugin-zipper.git
    cordova plugin add ./cordova-plugin-zipper
    ```

3. 接口测试

    编辑 `www/js/index.js` 文件，在 `onDeviceReady` 函数内加入如下语句并保存文件。

    ```js
    var success = function(message) {
        alert(message);
    }

    var failure = function() {
        alert("Error calling Zipper Plugin");
    }

    cordova.plugins.zipper.compress({
        zipfile: '/sdcard/compress.zip',
        file: '/sdcard/templates.json'
    }
    ```

4. 安装支持平台

    ```bash
    cordova platform add android
    ```

5. 构建应用

    ```bash
    cordova build
    ```    

6. 运行应用

    ```bash
    cordova run
    ```

## API接口

执行`npm run doc`，见 `out/index.html`

## 常见问题

* `libc++_shared.so`多次安装问题

    当多个插件同时存在`libc++_shared.so`时会存在冲突导致安装失败，一般可以在插件安装时加入`--force`选项强制安装。

    而 cordova-plugin-zipper 插件安装前会通过钩子函数自动判断是否存在 libc++_shared.so，不存在则复制到对应目录，

    卸载时则需要根据工程依赖自己决定是否删除 libc++_shared.so，无法自动删除。

## 参考引用

* [libzip](https://github.com/nih-at/libzip/)
