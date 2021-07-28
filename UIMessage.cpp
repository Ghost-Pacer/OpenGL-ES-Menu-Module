#include "UIMessage.h"

void
UIMessage::Write(UITextType key, char* value)
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

void
UIMessage::Write(UIWorkoutStage newStage)
{
	m_WorkoutStage = newStage;
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
UIMessage::Read(UITextType key)
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

UIWorkoutStage
UIMessage::ReadWorkoutStage()
{
	return m_WorkoutStage;
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
	delegate.Write(m_WorkoutStage);
	return delegate;
}

UIMessage
UIMessage::Delegate(UITextType key)
{
	UIMessage delegate = UIMessage();
	if (m_sValueMap.Exists(key)) {
		delegate.Write(key, m_sValueMap[key]);
	}
	delegate.SetTotalRacers(m_totalRacers);
	delegate.Write(m_UIAction);
	delegate.Write(m_UIState);
	delegate.Write(m_WorkoutStage);
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
	delegate.Write(m_WorkoutStage);
	return delegate;
}