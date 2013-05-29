#include "MyGUIManager.h" 

#include <cassert>  

//-----------------------------------------------------------------------------  
//MyGUISystem* MyGUISystem::ms_singleton = NULL;  
//-----------------------------------------------------------------------------  
MyGUIManager::~MyGUIManager()  
{  
      
}  
//-----------------------------------------------------------------------------  
bool MyGUIManager::destroy()  
{  
//    CEGUI::OgreRenderer::destroySystem();  
   // delete ms_singleton;  
   // ms_singleton = 0;  
    return true;  
}  
//-----------------------------------------------------------------------------  
CEGUI::MouseButton MyGUIManager::convertButton(OIS::MouseButtonID buttonId)  
{  
    switch(buttonId)  
    {  
    case OIS::MB_Left:  
        return CEGUI::LeftButton;  
    case OIS::MB_Right:  
        return CEGUI::RightButton;  
    case OIS::MB_Middle:  
        return CEGUI::MiddleButton;  
    default:  
        return CEGUI::LeftButton;  
    }  
}  
//-----------------------------------------------------------------------------  
bool MyGUIManager::init()  
{  
    if(!mGUIRender)  
    {  
        mGUIRender = &CEGUI::OgreRenderer::bootstrapSystem();  
        mGUISystem = CEGUI::System::getSingletonPtr();  
        //����GUI���⣬ ����Ĭ�ϲ���  
        CEGUI::Imageset::setDefaultResourceGroup("Imagesets");  
        CEGUI::Font::setDefaultResourceGroup("Fonts");  
        CEGUI::Scheme::setDefaultResourceGroup("Schemes");  
        CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");  
        CEGUI::WindowManager::setDefaultResourceGroup("Layouts");  

        CEGUI::SchemeManager::getSingleton().create("TaharezLook.scheme");  
        //CEGUI::FontManager::getSingleton().create("Batang-26.font");  
        //mGUISystem->setDefaultFont("Batang-26"); 
		//����Ĭ�������ʽ  
		setDefaultMouseCursor("TaharezLook", "MouseArrow");  

		/*CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
		CEGUI::Window *sheet = wmgr.createWindow("DefaultWindow", "CEGUIDemo/Sheet");*/

		/*CEGUI::Window *quit = wmgr.createWindow("TaharezLook/Button", "CEGUIDemo/QuitButton");
		quit->setText("enter game");
		quit->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.1, 0)));*/

		/*sheet->addChildWindow(quit);
		mGUISystem->setGUISheet(sheet);*/

// 		quit->subscribeEvent(CEGUI::PushButton::EventClicked,
// 			CEGUI::Event::Subscriber(&GameApp::getSingletonPtr->shutdown, this));
        /* 
         *  �˴�����ͼƬ��Դ(Imageset) 
         */  
        
        //����GUI����Ƿ�ɼ�  
        showGUICursor(true);  
        return true;  
    }  
    return false;  
}  

//-----------------------------------------------------------------------------
CEGUI::Window* MyGUIManager::createWindow(const std::string &type,std::string &name)
{
	return getWindowManager()->createWindow(type,name);
}

//-----------------------------------------------------------------------------  
void MyGUIManager::update(float timeSinceLastFrame)  
{  
    mGUISystem->injectTimePulse(timeSinceLastFrame);  
}  

//-----------------------------------------------------------------------------  
void MyGUIManager::createImageset(const std::string& name, const std::string& filename)  
{  
    CEGUI::ImagesetManager::getSingleton().createFromImageFile(name, filename);  
}  

//-----------------------------------------------------------------------------  
bool MyGUIManager::loadWindow(const std::string& layoutName)  
{  
    CEGUI::Window *guiSheet;  
    // ������layout���ļ��Ƿ����,û�м��������  
    if(!getGUIWindowManager()->isWindowPresent(layoutName))  
    {  
        // �� .layout�ű��ļ���ȡһ��UI������ƣ���������õ�GUI��Դ���С�  
        guiSheet = getGUIWindowManager()->loadWindowLayout(layoutName + ".layout");  
    }  
    else  
    {     
        // ����Ѿ�������ֱ����ʾ  
        guiSheet = getGUIWindowManager()->getWindow(layoutName);  
    }  
    // ���������Ǹ���CEGUI��ʾ�ķ�UI���֡���Ȼ���ǿ�����ʱ������ʾ��UI���֡�  
    mGUISystem->setGUISheet(guiSheet);  
    //��ʾUI����  
    guiSheet->show();  
    return true;  
}  

//-----------------------------------------------------------------------------  
bool MyGUIManager::destroyWindow(const std::string& windowName)  
{  
    getGUIWindowManager()->destroyWindow(windowName);  
    return true;  
}  

//-----------------------------------------------------------------------------  
void MyGUIManager::subscribeEvent(const CEGUI::String& windowName,  
    const CEGUI::String &eventName, const CEGUI::Event::Subscriber &subscriber)  
{  
    CEGUI::WindowManager::getSingleton().getWindow(CEGUI::String(windowName))  
        ->subscribeEvent(eventName,subscriber);  
}  

//-----------------------------------------------------------------------------  
void MyGUIManager::setProperty(const std::string& windowName,   
    const std::string& key, const std::string& value)  
{  
    MyGUIManager::getSingletonPtr()->getWindow(windowName)->setProperty(key, value);  
}  
//-----------