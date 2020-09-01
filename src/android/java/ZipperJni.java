package com.plugin.zipper;

public class ZipperJni {

    public static native int compress(int overwrite, int exclude, String zipfile, String file);

    public static native int uncompress(int overwrite, String zipfile, String targetpath);

    static {
        System.loadLibrary("zipper_jni");
    }
}
