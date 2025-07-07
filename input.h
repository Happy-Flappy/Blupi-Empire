

#ifndef KEY_EXTERNAL
#define KEY_EXTERNAL


#include <SFML/Graphics.hpp>

namespace Input
{
	
	
	
// Create a mapping of sf::Keyboard::Key values to their string names
std::vector<std::pair<std::string, sf::Keyboard::Key>> getKeyboardMapping() {
    std::vector<std::pair<std::string, sf::Keyboard::Key>> mapping;
    #define ADD_KEY(name) mapping.emplace_back(#name, sf::Keyboard::name)
    
    ADD_KEY(A); ADD_KEY(B); ADD_KEY(C); ADD_KEY(D); ADD_KEY(E);
    ADD_KEY(F); ADD_KEY(G); ADD_KEY(H); ADD_KEY(I); ADD_KEY(J);
    ADD_KEY(K); ADD_KEY(L); ADD_KEY(M); ADD_KEY(N); ADD_KEY(O);
    ADD_KEY(P); ADD_KEY(Q); ADD_KEY(R); ADD_KEY(S); ADD_KEY(T);
    ADD_KEY(U); ADD_KEY(V); ADD_KEY(W); ADD_KEY(X); ADD_KEY(Y); ADD_KEY(Z);
    ADD_KEY(Num0); ADD_KEY(Num1); ADD_KEY(Num2); ADD_KEY(Num3); ADD_KEY(Num4);
    ADD_KEY(Num5); ADD_KEY(Num6); ADD_KEY(Num7); ADD_KEY(Num8); ADD_KEY(Num9);
    ADD_KEY(Escape); ADD_KEY(LControl); ADD_KEY(LShift); ADD_KEY(LAlt);
    ADD_KEY(LSystem); ADD_KEY(RControl); ADD_KEY(RShift); ADD_KEY(RAlt);
    ADD_KEY(RSystem); ADD_KEY(Menu); ADD_KEY(LBracket); ADD_KEY(RBracket);
    ADD_KEY(SemiColon); ADD_KEY(Comma); ADD_KEY(Period); ADD_KEY(Quote);
    ADD_KEY(Slash); ADD_KEY(BackSlash); ADD_KEY(Tilde); ADD_KEY(Equal);
    ADD_KEY(Dash); ADD_KEY(Space); ADD_KEY(Return); ADD_KEY(BackSpace);
    ADD_KEY(Tab); ADD_KEY(PageUp); ADD_KEY(PageDown); ADD_KEY(End);
    ADD_KEY(Home); ADD_KEY(Insert); ADD_KEY(Delete); ADD_KEY(Add);
    ADD_KEY(Subtract); ADD_KEY(Multiply); ADD_KEY(Divide); ADD_KEY(Left);
    ADD_KEY(Right); ADD_KEY(Up); ADD_KEY(Down); ADD_KEY(Numpad0);
    ADD_KEY(Numpad1); ADD_KEY(Numpad2); ADD_KEY(Numpad3); ADD_KEY(Numpad4);
    ADD_KEY(Numpad5); ADD_KEY(Numpad6); ADD_KEY(Numpad7); ADD_KEY(Numpad8);
    ADD_KEY(Numpad9); ADD_KEY(F1); ADD_KEY(F2); ADD_KEY(F3); ADD_KEY(F4);
    ADD_KEY(F5); ADD_KEY(F6); ADD_KEY(F7); ADD_KEY(F8); ADD_KEY(F9);
    ADD_KEY(F10); ADD_KEY(F11); ADD_KEY(F12); ADD_KEY(F13); ADD_KEY(F14);
    ADD_KEY(F15); ADD_KEY(Pause);
    
    #undef ADD_KEY
    return mapping;
}

// Create a mapping of sf::Mouse::Button values to their string names
std::vector<std::pair<std::string, sf::Mouse::Button>> getMouseMapping() {
    return {
        {"Left", sf::Mouse::Left},
        {"Right", sf::Mouse::Right},
        {"Middle", sf::Mouse::Middle},
        {"XButton1", sf::Mouse::XButton1},
        {"XButton2", sf::Mouse::XButton2}
    };
}


	
	
	
	
    // Declare arrays with inline to avoid multiple definition errors
    inline bool keyDown[sf::Keyboard::KeyCount] = {false}; 
    inline bool keyTapped[sf::Keyboard::KeyCount] = {false};
    inline bool mouseDown[sf::Mouse::ButtonCount] = {false};
    inline bool mouseTapped[sf::Mouse::ButtonCount] = {false};
    
    inline sf::Vector2i mouseMove;
    inline sf::Event event;
    inline bool noKeyPressed = true;
	inline bool moving = false;
    

	bool Key(sf::Keyboard::Key input,bool tapping=false)
	{
		return tapping ? keyTapped[input] : keyDown[input];
	}
	
	
	
	
	
	// Reset frame-specific states (call this at start of each frame)
    void beginFrame()
    {
        for(int i = 0; i < sf::Keyboard::KeyCount; ++i) {
            keyTapped[i] = false;
        }
        for(int i = 0; i < sf::Mouse::ButtonCount; ++i) {
            mouseTapped[i] = false;
        }
        noKeyPressed = true;
        
       
	    
    }
	
	
	
	bool Mouse(sf::Mouse::Button input,bool tapping=false)
	{
		return tapping ? mouseTapped[input] : mouseDown[input];
	}
	
	
	
	bool MouseAny()
	{
		for(int a=0;a<sf::Mouse::ButtonCount;a++)
		{
			if(mouseDown[a])
				return true;
		}
		//else
		return false;
	}
	
	
	
	sf::Vector2i getPosition()
	{
		return mouseMove;
	}
	
	
	

	
	
	
	void update(sf::Event &e)
	{
		
		moving=false;
		
		event = e;
		//handle key press
		if (e.type == sf::Event::KeyPressed) 
		{
            int keyCode = e.key.code;
            if (keyCode >= 0 && keyCode < sf::Keyboard::KeyCount) 
			{
                if (!keyDown[keyCode]) // Only trigger once per press 
				{  
                    keyTapped[keyCode] = true;
                }
                keyDown[keyCode] = true;
                noKeyPressed = false;
            }
        }

        // Handle key release
        if (e.type == sf::Event::KeyReleased) 
		{
            int keyCode = e.key.code;
            if (keyCode >= 0 && keyCode < sf::Keyboard::KeyCount) 
			{
                keyDown[keyCode] = false;
            }
        }



	 





        if (e.type == sf::Event::MouseButtonPressed) 
		{
            int button = e.mouseButton.button;
            if (button >= 0 && button < sf::Mouse::ButtonCount) 
			{
                if (!mouseDown[button]) 
				{  
                    mouseTapped[button] = true; // Only trigger once per press
                }
                mouseDown[button] = true;
            }
        }
        else if (e.type == sf::Event::MouseButtonReleased) 
		{
            int button = e.mouseButton.button;
            if (button >= 0 && button < sf::Mouse::ButtonCount) 
			{
                mouseDown[button] = false;
            }
        }


		if(e.type == sf::Event::MouseMoved)
		{
			moving=true;
			mouseMove.x = e.mouseMove.x;
			mouseMove.y = e.mouseMove.y;
		}
		
		
	}
	
};



#endif
