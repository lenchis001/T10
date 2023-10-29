#ifndef TGAME
#define TGAME

#include "boost/smart_ptr.hpp"
#include "boost/config.hpp"

#include "irrlicht.h"

#include "IFunctionsProcessingAware.h"

class BOOST_SYMBOL_VISIBLE IGame
{
public:
	virtual void startGame(boost::shared_ptr<irr::IrrlichtDevice> device, boost::shared_ptr<IFunctionsProcessingAware> functionsProcessingAware) = 0;

	virtual void finishGame() = 0;

	virtual ~IGame(){};
};

#endif