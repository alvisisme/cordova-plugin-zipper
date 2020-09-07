const fs = require('fs')
const path = require('path')

const supportedAbis = ['arm64-v8a', 'armeabi-v7a', 'x86', 'x86_64']
const TAG = ' cordova-plugin-zipper: '

for (let abi of supportedAbis)
{
    const source = path.join('plugins', 'cordova-plugin-zipper', 'src', 'android', 'libs', abi, 'libc++_shared.so')
    const target = path.join('platforms', 'android', 'app', 'src', 'main', 'jniLibs', abi, 'libc++_shared.so')
    if (!fs.existsSync(target)) {
        console.info(TAG + 'not found ' + target + ', will add it!')
        fs.copyFileSync(source, target)
    }
}