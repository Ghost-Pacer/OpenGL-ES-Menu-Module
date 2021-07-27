#include "UIMessage.h"

void
UIMessage::Write(UIText key, char* value)
{
	m_sValueMap[key] = value;
}

void
UIMessage::Write(UIFloat key, float value)
{
	m_fValueMap[key] = value;
}

void
UIMessage::Write(UIBool key, bool value)
{
	m_bValueMap[key] = value;
}

void
UIMessage::Write(UIState state)
{
	m_UIState = state;
}

void
UIMessage::Write(UIAction action)
{
	m_UIAction = action;
}

float
UIMessage::Read(UIFloat key)
{
	if (m_fValueMap.Exists(key)) {
		return m_fValueMap[key];
	} else {
		return 0;
	}
}

char*
UIMessage::Read(UIText key)
{
	if (m_sValueMap.Exists(key)) {
		return m_sValueMap[key];
	} else {
		return 0;
	}
}

bool
UIMessage::Read(UIBool key)
{
	if (m_bValueMap.Exists(key)) {
		return m_bValueMap[key];
	} else {
		return false;
	}
}

UIState
UIMessage::ReadState()
{
	return m_UIState;
}

UIAction
UIMessage::ReadAction()
{
	return m_UIAction;
}

int
UIMessage::GetTotalRacers()
{
	return m_totalRacers;
}

void
UIMessage::SetTotalRacers(int total)
{
	m_totalRacers = total;
}

UIMessage
UIMessage::Delegate(UIFloat key)
{
	UIMessage delegate = UIMessage();
	if (m_fValueMap.Exists(key)) {
		delegate.Write(key, m_fValueMap[key]);
	}
	delegate.SetTotalRacers(m_totalRacers);
	delegate.Write(m_UIAction);
	delegate.Write(m_UIState);
	return delegate;
}

UIMessage
UIMessage::Delegate(UIText key)
{
	UIMessage delegate = UIMessage();
	if (m_sValueMap.Exists(key)) {
		delegate.Write(key, m_sValueMap[key]);
	}
	delegate.SetTotalRacers(m_totalRacers);
	delegate.Write(m_UIAction);
	delegate.Write(m_UIState);
	return delegate;
}

UIMessage
UIMessage::Delegate(UIBool key)
{
	UIMessage delegate = UIMessage();
	if (m_bValueMap.Exists(key)) {
		delegate.Write(key, m_bValueMap[key]);
	}
	delegate.SetTotalRacers(m_totalRacers);
	delegate.Write(m_UIAction);
	delegate.Write(m_UIState);
	return delegate;
}