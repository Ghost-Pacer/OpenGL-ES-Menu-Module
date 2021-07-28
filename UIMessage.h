#include "OGLES2Tools.h"

#ifndef _UIMESSAGE_H
#define _UIMESSAGE_H

enum UIFloat {
	UIStageProgress
};

enum UIText {
	UISpeedMPM,
	UIRank,
	UIEnergyKJ,
	UICalories,
	UITimeS,
	UIDistanceM,
	UINone
};

enum UIBool {
	UIHidden,
	UIButtonActive
};

enum UIState {
	UIMain,
	UIInfo,
	UIPause,
	UISummary
};

enum UIWorkoutStage {
	UIWarmup, 
	UIWorkout,
	UICooldown
};

enum UIAction {
	UINoAction,
	UIToggleActiveButton
};

class UIMessage
{
	protected:
		CPVRTMap<UIFloat, float> m_fValueMap;
		CPVRTMap<UIText, char*> m_sValueMap;
		CPVRTMap<UIBool, bool> m_bValueMap;
		UIState m_UIState;
		UIAction m_UIAction;
		UIWorkoutStage m_WorkoutStage;
		int m_totalRacers;
	public:
		void Write(UIFloat key, float value);
		void Write(UIText key, char* value);
		void Write(UIBool key, bool value);
		void Write(UIState state);
		void Write(UIAction action);
		void Write(UIWorkoutStage stage);
		void SetTotalRacers(int total);
		float Read(UIFloat key);
		char* Read(UIText key);
		bool Read(UIBool key);
		UIState ReadState();
		UIAction ReadAction();
		UIWorkoutStage ReadWorkoutStage();
		int GetTotalRacers();
		UIMessage Delegate(UIFloat key);
		UIMessage Delegate(UIText key);
		UIMessage Delegate(UIBool key);
};

#endif