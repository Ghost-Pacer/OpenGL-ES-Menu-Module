#include "OGLES2Tools.h"

#ifndef _UIMESSAGE_H
#define _UIMESSAGE_H

enum UIFloat {
	UIStageProgress
};

enum UITextType {
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
	UIButtonActive,
	UIMileMarker,
	UIBadge1,
	UIBadge2,
	UIBadge3
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
		CPVRTMap<UITextType, char*> m_sValueMap;
		CPVRTMap<UIBool, bool> m_bValueMap;
		UIState m_UIState;
		UIAction m_UIAction;
		UIWorkoutStage m_WorkoutStage;
		int m_totalRacers;
	public:
		void Write(UIFloat key, float value);
		void Write(UITextType key, char* value);
		void Write(UIBool key, bool value);
		void Write(UIState state);
		void Write(UIAction action);
		void Write(UIWorkoutStage stage);
		void SetTotalRacers(int total);
		float Read(UIFloat key);
		char* Read(UITextType key);
		bool Read(UIBool key);
		UIState ReadState();
		UIAction ReadAction();
		UIWorkoutStage ReadWorkoutStage();
		int GetTotalRacers();
		UIMessage Delegate(UIFloat key);
		UIMessage Delegate(UITextType key);
		UIMessage Delegate(UIBool key);
};

#endif