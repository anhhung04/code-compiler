const { Router } = require("express");
const { customInputTest } = require("../Controller/customInput");
const customInputRouter = Router();

customInputRouter.get("/", (req, res) => {
    res.render("customInput");
});

customInputRouter.post("/", customInputTest);

module.exports = customInputRouter;