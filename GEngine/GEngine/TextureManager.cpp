#include "TextureManager.h"
#include <OgreOverlayContainer.h>
#include <OgreOverlay.h>
void TextureManager::initialize()
{
	
	Ogre::v1::OverlayManager& overlayManager = Ogre::v1::OverlayManager::getSingleton();
    Ogre::v1::Overlay* overlay = overlayManager.create("OverlayName");

    // Create a panel
    Ogre::v1::OverlayContainer* panel = static_cast<Ogre::v1::OverlayContainer*>(overlayManager.createOverlayElement("Panel", "PanelName"));
    panel->setPosition(0.0, 0.0);
    panel->setDimensions(0.1, 0.1);
    panel->setMaterialName("BaseWhite");
    // Add the panel to the overlay
    overlay->add2D(panel);

    // Show the overlay
    overlay->show();
}
