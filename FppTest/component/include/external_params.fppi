external param ParamBoolExt: bool

external param ParamI32Ext: I32

external param ParamStringExt: string \
  default "external default"

external param ParamEnumExt: FormalParamEnum \
  id 0x50

external param ParamArrayExt: FormalParamArray \
  default [ 1.0, 2.0, 3.0 ] \
  save opcode 0x75

external param ParamStructExt: FormalParamStruct \
  set opcode 0x80 \
  save opcode 0x85
