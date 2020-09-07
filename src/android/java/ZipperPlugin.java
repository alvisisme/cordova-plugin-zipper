package com.plugin.zipper;

import org.apache.cordova.*;
import org.json.JSONArray;
import org.json.JSONException;

import java.io.File;

public class ZipperPlugin extends CordovaPlugin {

    @Override
    public boolean execute(String action, JSONArray data, CallbackContext callbackContext) {

        if (action.equals("compress")) {
            cordova.getThreadPool().execute(new Runnable() {
                public void run() {
                    try {
                        int overwrite = data.getInt(0);
                        int exclude = data.getInt(1);
                        String zipfile = data.getString(2);
                        String file = data.getString(3);

                        if (!(overwrite == 0 || overwrite == 1))  {
                            callbackContext.error("params error[overwrite]");
                            return;
                        }

                        if (!(exclude == 0 || exclude == 1)) {
                            callbackContext.error("params error[exclude]");
                            return;
                        }

                        if (zipfile.isEmpty()) {
                            callbackContext.error("params error[zipfile]");
                            return;
                        }

                        if (file.isEmpty()) {
                            callbackContext.error("params error[file]");
                            return;
                        }

                        File f = new File(file);
                        if (!f.exists()) {
                            callbackContext.error("params error[file], file " + file + " does not exist");
                            return;
                        }

                        int code = ZipperJni.compress(overwrite, exclude, zipfile, file);
                        if (code == 0) {
                            PluginResult pluginResult = new PluginResult(PluginResult.Status.OK);
                            callbackContext.sendPluginResult(pluginResult);
                        } else {
                            PluginResult pluginResult = new PluginResult(PluginResult.Status.ERROR,  "compress error[code=" + code + "]");
                            callbackContext.sendPluginResult(pluginResult);
                        }
                    } catch (JSONException e) {
                        PluginResult pluginResult = new PluginResult(PluginResult.Status.JSON_EXCEPTION,  e.getMessage());
                        callbackContext.sendPluginResult(pluginResult);
                    }
                }
            });
            return true;

        } else if (action.equals("uncompress")) {
            cordova.getThreadPool().execute(new Runnable() {
                public void run() {
                    try {
                        int overwrite = data.getInt(0);
                        String zipfile = data.getString(1);
                        String targetpath = data.getString(2);

                        if (!(overwrite == 0 || overwrite == 1)) {
                            callbackContext.error("params error[overwrite]");
                            return;
                        }

                        File file = new File(zipfile);
                        if (!file.exists()) {
                            callbackContext.error("params error[zipfile], file " + zipfile + " does not exist");
                            return;
                        }

                        File dir = new File(targetpath);
                        if (!dir.isDirectory()) {
                            callbackContext.error("params error[targetpath], file " + targetpath + " is not a directory");
                            return;
                        }

                        int code = ZipperJni.uncompress(overwrite, zipfile, targetpath);
                        if (code == 0) {
                            PluginResult pluginResult = new PluginResult(PluginResult.Status.OK);
                            callbackContext.sendPluginResult(pluginResult);
                        } else {
                            PluginResult pluginResult = new PluginResult(PluginResult.Status.ERROR, "uncompress error[code=" + code + "]");
                            callbackContext.sendPluginResult(pluginResult);
                        }
                    } catch (JSONException e) {
                        PluginResult pluginResult = new PluginResult(PluginResult.Status.JSON_EXCEPTION, e.getMessage());
                        callbackContext.sendPluginResult(pluginResult);
                    }
                }
            });
            return true;
        } else {
            return false;
        }
    }
}
