// ======================================================================
// \title  QueuedTest/test/ut/Tester.cpp
// \author tiffany
// \brief  cpp file for QueuedTest test harness implementation class
// ======================================================================

#include "STest/Pick/Pick.hpp"
#include "Tester.hpp"

// ----------------------------------------------------------------------
// Construction and destruction
// ----------------------------------------------------------------------

Tester ::Tester()
    : QueuedTestGTestBase("Tester", Tester::MAX_HISTORY_SIZE),
      component("QueuedTest"),
      primitiveBuf(primitiveData, sizeof(primitiveData)),
      stringBuf(stringData, sizeof(stringData)),
      enumBuf(enumData, sizeof(enumData)),
      arrayBuf(arrayData, sizeof(arrayData)),
      structBuf(structData, sizeof(structData)),
      serialBuf(serialData, sizeof(serialData)),
      time(STest::Pick::any(), STest::Pick::any()) {
    this->initComponents();
    this->connectPorts();
    this->connectAsyncPorts();
    this->component.registerExternalParameters(&this->paramTesterDelegate);
}

Tester ::~Tester() {}

void Tester ::initComponents() {
    this->init();
    this->component.init(Tester::TEST_INSTANCE_QUEUE_DEPTH, Tester::TEST_INSTANCE_ID);
}

Fw::ParamValid Tester ::from_prmGetIn_handler(const FwIndexType portNum, FwPrmIdType id, Fw::ParamBuffer& val) {
    val.resetSer();

    Fw::SerializeStatus status;
    U32 id_base = component.getIdBase();

    FW_ASSERT(id >= id_base);

    switch (id - id_base) {
        case QueuedTestComponentBase::PARAMID_PARAMBOOL:
            status = val.serialize(boolPrm.args.val);
            FW_ASSERT(status == Fw::FW_SERIALIZE_OK);
            break;

        case QueuedTestComponentBase::PARAMID_PARAMU32:
            status = val.serialize(u32Prm.args.val);
            FW_ASSERT(status == Fw::FW_SERIALIZE_OK);
            break;

        case QueuedTestComponentBase::PARAMID_PARAMSTRING:
            status = val.serialize(stringPrm.args.val);
            FW_ASSERT(status == Fw::FW_SERIALIZE_OK);
            break;

        case QueuedTestComponentBase::PARAMID_PARAMENUM:
            status = val.serialize(enumPrm.args.val);
            FW_ASSERT(status == Fw::FW_SERIALIZE_OK);
            break;

        case QueuedTestComponentBase::PARAMID_PARAMARRAY:
            status = val.serialize(arrayPrm.args.val);
            FW_ASSERT(status == Fw::FW_SERIALIZE_OK);
            break;

        case QueuedTestComponentBase::PARAMID_PARAMSTRUCT:
            status = val.serialize(structPrm.args.val);
            FW_ASSERT(status == Fw::FW_SERIALIZE_OK);
            break;
    }

    this->pushFromPortEntry_prmGetIn(id, val);

    return prmValid;
}

void Tester ::from_prmSetIn_handler(const FwIndexType portNum, FwPrmIdType id, Fw::ParamBuffer& val) {
    Fw::SerializeStatus status;
    U32 id_base = component.getIdBase();

    FW_ASSERT(id >= id_base);

    switch (id - id_base) {
        case QueuedTestComponentBase::PARAMID_PARAMBOOL:
            status = val.deserialize(boolPrm.args.val);
            FW_ASSERT(status == Fw::FW_SERIALIZE_OK);
            break;

        case QueuedTestComponentBase::PARAMID_PARAMU32:
            status = val.deserialize(u32Prm.args.val);
            FW_ASSERT(status == Fw::FW_SERIALIZE_OK);
            break;

        case QueuedTestComponentBase::PARAMID_PARAMSTRING:
            status = val.deserialize(stringPrm.args.val);
            FW_ASSERT(status == Fw::FW_SERIALIZE_OK);
            break;

        case QueuedTestComponentBase::PARAMID_PARAMENUM:
            status = val.deserialize(enumPrm.args.val);
            FW_ASSERT(status == Fw::FW_SERIALIZE_OK);
            break;

        case QueuedTestComponentBase::PARAMID_PARAMARRAY:
            status = val.deserialize(arrayPrm.args.val);
            FW_ASSERT(status == Fw::FW_SERIALIZE_OK);
            break;

        case QueuedTestComponentBase::PARAMID_PARAMSTRUCT:
            status = val.deserialize(structPrm.args.val);
            FW_ASSERT(status == Fw::FW_SERIALIZE_OK);
            break;
    }

    this->pushFromPortEntry_prmSetIn(id, val);
}

// ----------------------------------------------------------------------
// Unit test implementation of external parameter delegate serialization/deserialization
// ----------------------------------------------------------------------

Fw::SerializeStatus Tester::QueuedTestComponentBaseParamExternalDelegate ::
  deserializeParam(
      const FwPrmIdType base_id,
      const FwPrmIdType local_id,
      const Fw::ParamValid prmStat,
      Fw::SerializeBufferBase& buff
  )
{
  Fw::SerializeStatus stat;
  (void) base_id;

  // Serialize the parameter based on ID
  switch(local_id)
  {
    // ParamBoolExt
    case QueuedTestComponentBase::PARAMID_PARAMBOOLEXT:
      stat = buff.deserialize(this->m_param_ParamBoolExt);
      break;
    // ParamI32Ext
    case QueuedTestComponentBase::PARAMID_PARAMI32EXT:
      stat = buff.deserialize(this->m_param_ParamI32Ext);
      break;
    // ParamStringExt
    case QueuedTestComponentBase::PARAMID_PARAMSTRINGEXT:
      stat = buff.deserialize(this->m_param_ParamStringExt);
      break;
    // ParamEnumExt
    case QueuedTestComponentBase::PARAMID_PARAMENUMEXT:
      stat = buff.deserialize(this->m_param_ParamEnumExt);
      break;
    // ParamArrayExt
    case QueuedTestComponentBase::PARAMID_PARAMARRAYEXT:
      stat = buff.deserialize(this->m_param_ParamArrayExt);
      break;
    // ParamStructExt
    case QueuedTestComponentBase::PARAMID_PARAMSTRUCTEXT:
      stat = buff.deserialize(this->m_param_ParamStructExt);
      break;
    default:
      // Unknown ID should not have gotten here
      FW_ASSERT(false, local_id);
  }

  return stat;
}

Fw::SerializeStatus Tester::QueuedTestComponentBaseParamExternalDelegate ::
  serializeParam(
      const FwPrmIdType base_id,
      const FwPrmIdType local_id,
      Fw::SerializeBufferBase& buff
  ) const
{
  Fw::SerializeStatus stat;
  (void) base_id;

  // Serialize the parameter based on ID
  switch(local_id)
  {
    // ParamBoolExt
    case QueuedTestComponentBase::PARAMID_PARAMBOOLEXT:
      stat = buff.serialize(this->m_param_ParamBoolExt);
      break;
    // ParamI32Ext
    case QueuedTestComponentBase::PARAMID_PARAMI32EXT:
      stat = buff.serialize(this->m_param_ParamI32Ext);
      break;
    // ParamStringExt
    case QueuedTestComponentBase::PARAMID_PARAMSTRINGEXT:
      stat = buff.serialize(this->m_param_ParamStringExt);
      break;
    // ParamEnumExt
    case QueuedTestComponentBase::PARAMID_PARAMENUMEXT:
      stat = buff.serialize(this->m_param_ParamEnumExt);
      break;
    // ParamArrayExt
    case QueuedTestComponentBase::PARAMID_PARAMARRAYEXT:
      stat = buff.serialize(this->m_param_ParamArrayExt);
      break;
    // ParamStructExt
    case QueuedTestComponentBase::PARAMID_PARAMSTRUCTEXT:
      stat = buff.serialize(this->m_param_ParamStructExt);
      break;
    default:
      // Unknown ID should not have gotten here
      FW_ASSERT(false, local_id);
  }

  return stat;
}
