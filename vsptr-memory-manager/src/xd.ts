const ffi = require('ffi-napi');



const client = new ffi.Library('/home/sebasmora/Documents/TEC/Semestre III/Datos II/VS-Code-Memory-Manager/vsptr-memory-manager/lib/libVSCode', {
    'getGarbageCollectorList':[
        'string',[]
    ]
});

console.log(client.getGarbageCollectorList());


