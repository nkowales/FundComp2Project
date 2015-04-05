/*
 * OneWayPlatform.h
 *
 *  Created on: Apr 4, 2015
 *      Author: naiello
 */

#ifndef ONEWAYPLATFORM_H_
#define ONEWAYPLATFORM_H_

#include "Block.h"

// Don't know if we actually need a full class for this or just make it a flag in the original block class
// keeping it as a separate class right now in case we need to treat differently for collision handling

class OneWayPlatform : public Block
{
public:
	OneWayPlatform(Uint32);

};

#endif /* ONEWAYPLATFORM_H_ */
