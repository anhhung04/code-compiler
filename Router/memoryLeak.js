const { Router } = require("express");
const {
    renderUploadFiles,
    sendMemoryLeakFiles,
} = require("../Controller/memoryLeak");

const memoryLeakRouter = new Router();

memoryLeakRouter.get("/", renderUploadFiles);

memoryLeakRouter.post("/", sendMemoryLeakFiles);

module.exports = memoryLeakRouter;
