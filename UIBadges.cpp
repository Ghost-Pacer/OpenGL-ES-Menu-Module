#include "UIBadges.h"

UIBadges::UIBadges(float x, float y)
{
	m_x = x;
	m_y = y;
	m_badges.Reserve(c_numBadges);
	m_activeBadges = CPVRTArray<UIImage*>(c_numBadges);
	for ( int i = 0; i < c_numBadges; i ++) {
		UIBadge badge = c_Badges[i];
		m_badges[badge.identifier] = new UIImage(badge.imageName, m_x, m_y, badge.width, badge.height);
	}
	Test();
}

void
UIBadges::Test()
{
	AddBadge(UIBadge1);
	AddBadge(UIBadge2);
	AddBadge(UIBadge3);
}

bool
UIBadges::AddBadge(UIBool identifier)
{
	if (!m_badges.Exists(identifier)) {
		return false;
	} else {
		UIImage* badge = m_badges[identifier];
		int numImages;
		if ((numImages = m_activeBadges.GetSize()) == 0) {
			m_activeBadges.Append(badge);
			return true;
		} else {
			for ( int i = 0; i < numImages; i ++ ) {
				m_activeBadges[i]->Move(-c_badgeDim-4, 0);
			}
			badge->Move(numImages*c_badgeDim+4, 0);
			m_activeBadges.Append(badge);
			return true;
		}
	}
	return true;
}

bool
UIBadges::LoadTextures(CPVRTString* const pErrorStr)
{
	if (m_badges.GetSize() > 0) {
		for ( int i = 0 ; i < m_badges.GetSize(); i ++ ) {
			if (m_badges.GetDataAtIndex(i) != NULL && !(*m_badges.GetDataAtIndex(i))->LoadTextures(pErrorStr)) {
				return false;
			} else {
				fprintf(stderr, "Badge texture successfully loaded\n");
			}
		}
	}
	return true;
}

void
UIBadges::BuildVertices()
{
	if (m_badges.GetSize() > 0) {
		for ( int i = 0 ; i < m_badges.GetSize(); i ++ ) {
			UIImage* badge = *m_badges.GetDataAtIndex(i);
			if (badge != NULL) {
				badge->BuildVertices();
			}
		}
	}
}

bool
UIBadges::Render(GLuint uiMVPMatrixLoc, UIPrinter* printer)
{
	if (m_activeBadges.GetSize() > 0 && !m_hidden) {
		for ( int i = 0 ; i < m_activeBadges.GetSize(); i ++ ) {
			UIImage* badge = m_activeBadges[i];
			if (badge != NULL && !badge->Render(uiMVPMatrixLoc, printer)) {
				return false;
			}
		}
	}
	return true;
}

void
UIBadges::Update(UIMessage updateMessage)
{
	fprintf(stderr, "Updating badges\n");
	if (updateMessage.Read(UIBadge1)) {
		fprintf(stderr, "Adding badge\n");
		AddBadge(UIBadge1);
	} else if (updateMessage.Read(UIBadge2)) {
		AddBadge(UIBadge2);
	} else if (updateMessage.Read(UIBadge3)) {
		AddBadge(UIBadge3);
	} else {
		return;
	}
}

void
UIBadges::Hide()
{
	m_hidden = true;
}

void
UIBadges::Show()
{
	m_hidden = false;
}