
import QuantLibParser as qlp
from QuantLibParser.CommonSchemas import *

schema = {"type": "array"}
data = {}
qlp.schemaValidation(schema, data)
