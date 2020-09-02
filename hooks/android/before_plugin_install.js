const fs = require('fs')
const path = require('path')

const archTypes = ['arm64-v8a', 'armeabi-v7a', 'x86', 'x86_64']

for (let arch of archTypes)
{
    const shared_lib = path.join('platforms', 'android', 'app', 'src', 'main', 'jniLibs', arch, 'libc++_shared.so')
    if (fs.existsSync(shared_lib)) {
        console.warn(' found ' + shared_lib + ' already exists, this plugin will replace it!!!')
        fs.unlinkSync(shared_lib)
    }
}
