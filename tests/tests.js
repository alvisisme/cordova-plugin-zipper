exports.defineAutoTests = function () {
    describe('Zipper Information (window.cordova.plugins.zipper)', function () {
        it('should exist', function () {
            expect(window.cordova).toBeDefined();
            expect(window.cordova.plugins).toBeDefined();
            expect(window.cordova.plugins.zipper).toBeDefined();
        });

        it('should contain a compress property that is a function', function () {
            expect(typeof window.cordova.plugins.zipper.compress === 'function').toBe(true);            
        });

        it('should contain a uncompress property that is a function', function () {
            expect(typeof window.cordova.plugins.zipper.uncompress === 'function').toBe(true);   
        });
    });
};

exports.defineManualTests = function (contentEl, createActionButton) {
    var logMessage = function (message, color) {
        var log = document.getElementById('info');
        var logLine = document.createElement('div');
        if (color) {
            logLine.style.color = color;
        }
        logLine.innerHTML = message;
        log.appendChild(logLine);
    };

    var clearLog = function () {
        var log = document.getElementById('info');
        log.innerHTML = '';
    };

    var device_tests =
        '<h3>Create a test.json file in /sdcard before test</h3>' +
        '<div id="placeholder_for_buttons"></div>';

    contentEl.innerHTML = '<div id="info"></div>' + device_tests;

    // TODO: request external sdcard write permission ?
    createActionButton(
        'Compress',
        function () {
            clearLog();
            const options = {
                overwrite: 1,
                zipfile: '/sdcard/test.zip',
                file: '/sdcard/test.json'
            }
            cordova.plugins.zipper.compress(options, function () {
                logMessage('compress success', null, '\t');
            }, function (error) {
                logMessage('compress error ' + error, null, '\t');
            })
        },
        'placeholder_for_buttons'
    );

    createActionButton(
        'Uncompress',
        function () {
            clearLog();
            const options = {
                overwrite: 1,
                zipfile: '/sdcard/test.zip',
                targetpath: '/sdcard/'
            }
            cordova.plugins.zipper.uncompress(options, function () {
                logMessage('uncompress success', null, '\t');
            }, function (error) {
                logMessage('uncompress error ' + error, null, '\t');
            })
        },
        'placeholder_for_buttons'
    );
};
