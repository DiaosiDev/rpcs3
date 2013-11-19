#include "stdafx.h"
#include "PPCThread.h"
#include "Gui/InterpreterDisAsm.h"

PPCThread* GetCurrentPPCThread()
{
	CPUThread* thread = GetCurrentCPUThread();

	if(!thread || (thread->GetType() != CPU_THREAD_PPU && thread->GetType() != CPU_THREAD_SPU && thread->GetType() != CPU_THREAD_RAW_SPU))
	{
		throw wxString("GetCurrentPPCThread: bad thread");
	}

	return (PPCThread*)thread;
}

PPCThread::PPCThread(CPUThreadType type) : CPUThread(type)
{
}

PPCThread::~PPCThread()
{
	Close();
}

void PPCThread::DoReset()
{
	memset(m_args, 0, sizeof(u64) * 4);
}

void PPCThread::InitStack()
{
	if(m_stack_addr) return;
	if(m_stack_size == 0) m_stack_size = 0x10000;
	m_stack_addr = Memory.StackMem.Alloc(Memory.AlignAddr(m_stack_size, 0x100));

	m_stack_point = m_stack_addr + m_stack_size;
	/*
	m_stack_point += m_stack_size - 0x10;
	m_stack_point &= -0x10;
	Memory.Write64(m_stack_point, 0);
	m_stack_point -= 0x60;
	Memory.Write64(m_stack_point, m_stack_point + 0x60);
	*/
}
