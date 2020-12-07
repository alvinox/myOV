import logging
logging.basicConfig(
    level = logging.DEBUG,
    filename = "debug.log",
    filemode = "w",
    format = "%(filename)10s:%(lineno)4d:%(message)s"
)
log = logging.getLogger()