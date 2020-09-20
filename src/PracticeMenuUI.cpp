#include "../include/main.hpp"

#include "../extern/beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "../extern/beatsaber-hook/shared/utils/il2cpp-functions.hpp"
#include "../extern/beatsaber-hook/shared/utils/utils.h"
#include "../extern/custom-ui/shared/customui.hpp"
#include <cmath>

void GetNJS();
void GetOffset();
void IncreaseNJS();
void DecreaseNJS();
void ResetNJS();
void IncreaseOffset();
void DecreaseOffset();
void ResetOffset();

using namespace il2cpp_utils;


TextObject NJSText;
TextObject OffsetText;

CustomButton NJSIncrease;
CustomButton NJSDecrease;
CustomButton NJSReset;

CustomButton OffsetIncrease;
CustomButton OffsetDecrease;
CustomButton OffsetReset;

std::string oldsongname;
int olddiff;

void NJSUI(Il2CppObject* button, Il2CppObject* parent){
    Vector2 NJSTextPos = {10.0f, -1.0f};

    NJSIncrease.parent = button;
    NJSIncrease.parentTransform = parent;
    NJSIncrease.text = ">";
    NJSIncrease.scale = {0.3f, 0.3f, 1.0f};
    NJSIncrease.onPress = IncreaseNJS;
    NJSIncrease.sizeDelta = {-27.0f, 5.75f, 0.0f};
    NJSIncrease.create();

    NJSDecrease.parent = button;
    NJSDecrease.parentTransform = parent;
    NJSDecrease.text = "<";
    NJSDecrease.scale = {0.3f, 0.3f, 1.0f};
    NJSDecrease.onPress = DecreaseNJS;
    NJSDecrease.sizeDelta = {-47.0f, 5.75f, 0.0f};
    NJSDecrease.create();

    NJSReset.parent = button;
    NJSReset.parentTransform = parent;
    NJSReset.text = "RESET";
    NJSReset.scale = {0.3f, 0.3f, 1.0f};
    NJSReset.onPress = ResetNJS;
    NJSReset.sizeDelta = {-18.0f, 5.75f, 0.0f};
    NJSReset.create();

    NJSText.anchoredPosition = NJSTextPos;
    NJSText.fontSize = 4.5f;
    NJSText.parentTransform = parent;
    NJSText.text = "NJS: " + std::to_string((int)customNjs);
    NJSText.create();
}

void OffsetUI(Il2CppObject* button, Il2CppObject* parent){
    Vector2 OffsetTextPos = {69.0f, -1.0f};
    
    OffsetIncrease.parent = button;
    OffsetIncrease.parentTransform = parent;
    OffsetIncrease.text = ">";
    OffsetIncrease.scale = {0.3f, 0.3f, 1.0f};
    OffsetIncrease.onPress = IncreaseOffset;
    OffsetIncrease.sizeDelta = {38.0f, 5.75f, 0.0f};
    OffsetIncrease.create();

    OffsetDecrease.parent = button;
    OffsetDecrease.parentTransform = parent;
    OffsetDecrease.text = "<";
    OffsetDecrease.scale = {0.3f, 0.3f, 1.0f};
    OffsetDecrease.onPress = DecreaseOffset;
    OffsetDecrease.sizeDelta = {12.0f, 5.75f, 0.0f};
    OffsetDecrease.create();

    OffsetReset.parent = button;
    OffsetReset.parentTransform = parent;
    OffsetReset.text = "RESET";
    OffsetReset.scale = {0.3f, 0.3f, 1.0f};
    OffsetReset.onPress = ResetOffset;
    OffsetReset.sizeDelta = {47.0f, 5.75f, 0.0f};
    OffsetReset.create();

    OffsetText.anchoredPosition = OffsetTextPos;
    OffsetText.fontSize = 4.5f;
    OffsetText.parentTransform = parent;
    OffsetText.text = "Offset: " + std::to_string(customOffset).substr(0,4);
    OffsetText.create();
}

void CreatePracticeMenuUI(Il2CppObject* self){
    Il2CppObject* songNameUGUI = *GetFieldValue(self, "_songNameText");
    Il2CppString* songName = CRASH_UNLESS(RunMethod<Il2CppString*>(songNameUGUI, "get_text"));
    std::string songNamestr = to_utf8(csstrtostr(songName));
    // Bit scuff but it works so fuck it
    if(songNamestr != oldsongname || diff != olddiff)
    { 
        GetNJS(); 
        GetOffset(); 
        olddiff = diff; 
        oldsongname = songNamestr;
    }
    Il2CppObject* slider = *GetFieldValue(self, "_songStartSlider");
    Il2CppObject* playButton = *GetFieldValue(self, "_playButton");
    Il2CppObject* go = *RunMethod(slider, "get_transform");
    Il2CppObject* parent = *RunMethod(go, "get_parent");
    NJSUI(playButton, parent);
    OffsetUI(playButton, parent);
}

void GetNJS(){
    customNjs = defaultNjs;
}
void GetOffset(){
    customOffset = defaultOffset;
}
void ResetNJS(){
    customNjs = defaultNjs;
    NJSText.set("NJS: " + std::to_string((int)customNjs));
}
void IncreaseNJS(){
    if(customNjs < 99){
        customNjs++;
        NJSText.set("NJS: " + std::to_string((int)customNjs));
    }
}
void DecreaseNJS(){
    if(customNjs > -99){
        customNjs--;
        NJSText.set("NJS: " + std::to_string((int)customNjs));
    }
}


void ResetOffset(){
    customOffset = defaultOffset;
    OffsetText.set("Offset: " + std::to_string(customOffset).substr(0,4));
}
void IncreaseOffset(){
    if(customOffset < 9.9f){
        customOffset += 0.1f;
        OffsetText.set("Offset: " + std::to_string(customOffset).substr(0,4));
    }
}
void DecreaseOffset(){
    if(customOffset > -9.9f){
        customOffset -= 0.1f;
        OffsetText.set("Offset: " + std::to_string(customOffset).substr(0,4));
    }
}

void DestroyPracticeUI(){
    OffsetText.destroy();
    OffsetIncrease.destroy();
    OffsetDecrease.destroy();
    OffsetReset.destroy();

    NJSText.destroy();
    NJSIncrease.destroy();
    NJSDecrease.destroy();
    NJSReset.destroy();
}
