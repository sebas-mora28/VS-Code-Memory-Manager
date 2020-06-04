const ffi = require('ffi-napi');



const client = ffi.Library('/home/sebasmora/Desktop/ffd' + '/lib/libVSCodeRemote', {
    'testConnection':[
        'void',[]
    ]
});

client.testConnection();


