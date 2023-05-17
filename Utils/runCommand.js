const { workerData, parentPort } = require("node:worker_threads");
const { spawn } = require("node:child_process");

const child = spawn(workerData.command, workerData.args, workerData.options);

let data = "";
let error = "";
child.stdout.on("data", (chunk) => {
    data += chunk;
});

child.stderr.on("data", (chunk) => {
    error += chunk;
});

child.on("close", (code) => {
    parentPort.postMessage({ code, stdout: data, stderr: error });
});