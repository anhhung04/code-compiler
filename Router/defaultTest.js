const { Router } = require("express");
const { sendDefaultFiles } = require("../Controller/defaultTest");

const defaultTestRouter = new Router();

defaultTestRouter.post("/", sendDefaultFiles);

module.exports = defaultTestRouter;
