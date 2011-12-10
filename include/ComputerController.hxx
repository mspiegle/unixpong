#ifndef _COMPUTERCONTROLLER_H_
#define _COMPUTERCONTROLLER_H_

#include "ControllerBase.hxx"

class ComputerController : public ControllerBase {
	public:
		ComputerController();
		~ComputerController();

		int GetY();
};

#endif
