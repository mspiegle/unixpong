#ifndef _COMPUTERCONTROLLER_H_
#define _COMPUTERCONTROLLER_H_

#include <ControllerBase.h>

class ComputerController : public ControllerBase {
	public:
		ComputerController();
		~ComputerController();

		int GetY();
};

#endif
