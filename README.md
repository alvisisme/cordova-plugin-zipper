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

## 接口

见 [源码注释](./www/zipper.js)

## 参考引用

* [libzip](https://github.com/nih-at/libzip/)
