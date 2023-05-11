const { Router } = require("express");
const { compileExecFiles } = require("../Controller/compile");

const compileRouter = new Router();

compileRouter.post("/", compileExecFiles);

module.exports = compileRouter;
