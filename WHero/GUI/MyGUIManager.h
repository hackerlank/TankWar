
#ifndef _MYGUIMANAGER_H_
#define _MYGUIMANAGER_H_

#include <OIS/OIS.h>
#include <CEGUI.h>
#include <RendererModules/Ogre/CEGUIOgreRenderer.h>
#include "../Common/SingletonT.h"

#pragma  once


class MyGUIManager  : public SingletonT<MyGUIManager>
{  
	SINGLETON_DEFINE(MyGUIManager)
public:  
    virtual ~MyGUIManager();  

    //��OIS�����IDת����CEGUI�����ID  
    static CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonId);  

    //������Դ  
    bool destroy();

    //��ʼ��CEGUI�� ������RenderWindow��ʼ���ʼ, ֻ�ڵ�һ�ε�����Ч  
    bool init();  

	//--------------------��������---------------------------------------
	CEGUI::Window*createWindow(const std::string &type,std::string &name);
	CEGUI::WindowManager*getWindowManager(){return CEGUI::WindowManager::getSingletonPtr();}  
  //GUI����  
    void update(float timeSinceLastFrame);  
	//void setTargetSceneManager(Ogre::SceneManager*mgr){mGUIRender->setTargetSceneManager();}
    /** 
    ����ͼƬ����Imageset 
    params: 
    @name       ������Imageset����, ȫ��Ψһ 
    @filename   ����Imageset��ͼƬ���� 
    */  
    static void createImageset(const std::string& name, const std::string& filename);  

    //����layout  
    bool loadWindow(const std::string& layoutName);  

    //�õ�ָ�����ƵĴ���  
    inline CEGUI::Window* getWindow(const std::string& windowName)   
    {  
        return getGUIWindowManager()->getWindow(windowName);   
    }  

    //����ָ�����ƵĴ���  
    bool destroyWindow(const std::string& windowName);  
    /* 
    *   ��ָ�����ƵĴ����趨���� 
    params: 
    @windowName �������� 
    @key            XML��ǩ  keyֵ 
    @value          XML��ǩ  valueֵ 
    */  
    static void setProperty(const std::string& windowName, const std::string& key,   
        const std::string& value);  
    /** 
    ע��CEGUI�ؼ��¼� 
    params: 
    @windowName     Ҫע���¼��Ŀؼ����� 
    @eventName      ע��Ŀؼ��¼� 
    @subscriber     �¼�����ʱ�Ļص����� 
    */  
    static void subscribeEvent(const CEGUI::String& windowName,   
        const CEGUI::String &eventName,   
        const CEGUI::Event::Subscriber &subscriber);  
    //�õ����ڹ�������������ȡ����GUI�Ĵ��ڶ���Ĺ�����  
    inline CEGUI::WindowManager* getGUIWindowManager()  
    {  
        return CEGUI::WindowManager::getSingletonPtr();  
    }  
    // ע��CEGUI������¼�  
    bool injectMouseButtonDown(CEGUI::MouseButton id)   
    {  
        return mGUISystem->injectMouseButtonDown(id);  
    }  
    bool injectMouseButtonUp(CEGUI::MouseButton id)   
    {  
        return mGUISystem->injectMouseButtonUp(id);   
    }  
    // ע��CEGUI����ƶ��¼�  
    bool injectMouseMove(float xRel, float yRel)  
    {  
        return mGUISystem->injectMouseMove(xRel, yRel);  
    }  
    //��ʾ/����GUI���  
    inline void showGUICursor(bool showCursor)  
    {  
        if(showCursor)  
        {  
            CEGUI::MouseCursor::getSingleton().show();  
        }  
        else  
        {  
            CEGUI::MouseCursor::getSingleton().hide();  
        }  
        //����ϵͳ���;
       // ::ShowCursor(false);  
    }  
    /* 
    *   ����Ĭ�������ʽ 
    params: 
    @schemeName ��ʽ���� 
    @mouseName      ��ʽ�е�������� 
    */  
    inline void setDefaultMouseCursor(const std::string& schemeName, const std::string& mouseName)   
    {  
        CEGUI::System::getSingleton().setDefaultMouseCursor(schemeName, mouseName);  
        CEGUI::MouseCursor::getSingleton().setImage(mGUISystem->getDefaultMouseCursor());  
    }  
public:  
    /* 
    *   ����ʵ������ 
    */  
	/*
    static MyGUISystem* getSingletonPtr()  
    {  
        if(ms_singleton == NULL)  
        {  
            ms_singleton = new MyGUISystem;  
        }  
        return ms_singleton;  
    }  */
private:  
    //����ʵ��ָ��  
    //static MyGUISystem* ms_singleton;  
private:  
    CEGUI::OgreRenderer* mGUIRender;  
    CEGUI::System*       mGUISystem;  
private:  
    /* 
    *   ˽�л�ʵ��������ʵ�ֵ��� 
    */  
    MyGUIManager()  
        :mGUIRender(0), mGUISystem(0)  
    {}  
    MyGUIManager(const MyGUIManager&);  
    MyGUIManager& operator=(const MyGUIManager&);  
}; 

#endif