// Main.cpp //

#include "stdafx.h"

#include "Core.h"

int _tmain(int argc, _TCHAR* argv[]){
	Core m_xCore;

	if (!m_xCore.Init()){
		return 0;
	}

	m_xCore.Run();
	m_xCore.Cleanup();

	return 0;
}