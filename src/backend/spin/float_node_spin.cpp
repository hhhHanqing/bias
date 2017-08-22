#include "float_node_spin.hpp"
#include "basic_types.hpp"
#include "exception.hpp"
#include <sstream>


namespace bias
{
    spinNodeType FloatNode_spin::ExpectedType()
    {
        return FloatNode;
    }


    FloatNode_spin::FloatNode_spin() : NumberNode_spin() 
    {
        initialize();
    }


    FloatNode_spin::FloatNode_spin(spinNodeHandle hNode) : NumberNode_spin(hNode)
    {
        if (!isOfType(ExpectedType()))
        {
            std::stringstream ssError;
            ssError << __PRETTY_FUNCTION__;
            ssError << ": incorrect node type";
            throw RuntimeError(ERROR_SPIN_INCORRECT_NODE_TYPE, ssError.str());
        }
        initialize();
    }


    FloatNode_spin::FloatNode_spin(BaseNode_spin node)
    {
        hNode_ = node.handle();
        initialize();
    }



    std::string FloatNode_spin::unit()
    {
        checkNodeHandle();
        checkAvailable();
        checkReadable();

        char buffer[MAX_BUF_LEN];
        size_t bufferLen = MAX_BUF_LEN;
        spinError err = spinFloatGetUnit(hNode_,buffer,&bufferLen);
        if (err != SPINNAKER_ERR_SUCCESS)
        {
            std::stringstream ssError;
            ssError << __PRETTY_FUNCTION__;
            ssError << ": unable to get string node value, error = " << err;
            throw RuntimeError(ERROR_SPIN_GET_NUMBER_UNIT, ssError.str());
        }
        return std::string(buffer);
    }


    // Protected methods
    // --------------------------------------------------------------------------------------------
    void FloatNode_spin::initialize()
    {
        getValFunc_ = spinFloatGetValue;
        setValFunc_ = spinFloatSetValue;
        getMinFunc_ = spinFloatGetMin;
        getMaxFunc_ = spinFloatGetMax;
    }

} // namespace bias
