#include "../include/main.hpp"

#include "../extern/beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "../extern/beatsaber-hook/shared/utils/il2cpp-functions.hpp"
#include "../extern/beatsaber-hook/shared/utils/utils.h"
#include "../extern/custom-ui/shared/customui.hpp"
#include <cmath>



void IncreaseNJSPause();
void DecreaseNJSPause();
void IncreaseOffsetPause();
void DecreaseOffsetPause();


TextObject njs;
TextObject NJSTextPause;
CustomButton NJSIncreasePause;
CustomButton NJSDecreasePause;

TextObject offset;
TextObject OffsetTextPause;
CustomButton OffsetIncreasePause;
CustomButton OffsetDecreasePause;



void CreateNJSUI(Il2CppObject* button, Il2CppObject* parent){
    NJSIncreasePause.parent = button;
    NJSIncreasePause.parentTransform = parent;
    NJSIncreasePause.text = ">";
    NJSIncreasePause.scale = {0.25f, 0.5f, 1.0f};
    NJSIncreasePause.onPress = IncreaseNJSPause;
    NJSIncreasePause.sizeDelta = {38.5f, -25.0f, 0.0f};
    NJSIncreasePause.create();

    NJSDecreasePause.parent = button;
    NJSDecreasePause.parentTransform = parent;
    NJSDecreasePause.text = "<";
    NJSDecreasePause.scale = {0.25f, 0.5f, 1.0f};
    NJSDecreasePause.onPress = DecreaseNJSPause;
    NJSDecreasePause.sizeDelta = {18.5f, -25.0f, 0.0f};
    NJSDecreasePause.create();

    njs.anchoredPosition = {50.0f, -65.0f};
    njs.fontSize = 5.0f;
    njs.parentTransform = parent;
    njs.text = "NJS";
    njs.create();

    NJSTextPause.anchoredPosition = {102.0f, -65.0f};
    NJSTextPause.fontSize = 4.5f;
    NJSTextPause.parentTransform = parent;
    NJSTextPause.text = customNjs == defaultNjs ? "<u>" + std::to_string((int)customNjs) + "</u>" : std::to_string((int)customNjs);
    NJSTextPause.create();
}

void CreateOffsetUI(Il2CppObject* button, Il2CppObject* parent){
    OffsetIncreasePause.parent = button;
    OffsetIncreasePause.parentTransform = parent;
    OffsetIncreasePause.text = ">";
    OffsetIncreasePause.scale = {0.25f, 0.5f, 1.0f};
    OffsetIncreasePause.onPress = IncreaseOffsetPause;
    OffsetIncreasePause.sizeDelta = {38.5f, -30.0f, 0.0f};
    OffsetIncreasePause.create();

    OffsetDecreasePause.parent = button;
    OffsetDecreasePause.parentTransform = parent;
    OffsetDecreasePause.text = "<";
    OffsetDecreasePause.scale = {0.25f, 0.5f, 1.0f};
    OffsetDecreasePause.onPress = DecreaseOffsetPause;
    OffsetDecreasePause.sizeDelta = {18.5f, -30.0f, 0.0f};
    OffsetDecreasePause.create();

    offset.anchoredPosition = {50.0f, -70.0f};
    offset.fontSize = 5.0f;
    offset.parentTransform = parent;
    offset.text = "Offset";
    offset.create();

    OffsetTextPause.anchoredPosition = {102.0f, -70.0f};
    OffsetTextPause.fontSize = 4.5f;
    OffsetTextPause.parentTransform = parent;
    OffsetTextPause.text = customOffset == defaultOffset ? "<u>" + std::to_string(customOffset).substr(0,customOffset < 0 ? 4 : 3) + "</u>" : std::to_string(customOffset).substr(0, customOffset < 0 ? 4 : 3);
    OffsetTextPause.create();
}

void CreateInMapUI(Il2CppObject* self){
    Il2CppObject* continueButton = *GetFieldValue(self, "_continueButton");

    Il2CppObject* pause = *RunMethod(GetClassFromName("UnityEngine", "GameObject"), "Find", createcsstr("PauseMenu"));
    Il2CppObject* pauseTransform = *RunMethod(pause, "get_transform");
    Il2CppObject* wrapper = *RunMethod(pauseTransform, "Find", createcsstr("Wrapper"));
    Il2CppObject* ui = *RunMethod(wrapper, "Find", createcsstr("UI"));
    Il2CppObject* bg = *RunMethod(ui, "Find", createcsstr("BG"));

    Il2CppObject* canvas = *RunMethod(ui, "Find", createcsstr("Canvas"));
    Il2CppObject* canvTrans = *RunMethod(canvas, "get_transform");

    Vector3 pos = *RunMethod<Vector3>(bg, "get_localPosition");
    pos = {pos.x, pos.y - 0.35f, pos.z};
    RunMethod(bg, "set_localPosition", pos);
    
    pos = *RunMethod<Vector3>(pauseTransform, "get_localPosition");
    pos = {pos.x, pos.y + 0.175f, pos.z};
    RunMethod(pauseTransform, "set_localPosition", pos);
    
    CreateNJSUI(continueButton, canvTrans);
    CreateOffsetUI(continueButton, canvTrans);
}


void UpdateSpawnMovementData(){
    Il2CppObject* spawnMovementData = *GetFieldValue(_spawnController, "_beatmapObjectSpawnMovementData");
    Il2CppObject* vbpm = *GetFieldValue(_spawnController, "_variableBPMProcessor");
    float bpm = *RunMethod<float>(vbpm, "get_currentBPM");
    SetFieldValue(spawnMovementData, "_startNoteJumpMovementSpeed", customNjs);
    SetFieldValue(spawnMovementData, "_noteJumpStartBeatOffset", customOffset);
    RunMethod(spawnMovementData, "Update", bpm, *GetFieldValue<float>(_spawnController, "_jumpOffsetY"));
}


void IncreaseNJSPause(){
    if(customNjs < 99) customNjs++;
    NJSTextPause.set(customNjs == defaultNjs ? "<u>" + std::to_string((int)customNjs) + "</u>" : std::to_string((int)customNjs));
    UpdateSpawnMovementData();
}
void DecreaseNJSPause(){
    if(customNjs > -99) customNjs--;
    NJSTextPause.set(customNjs == defaultNjs ? "<u>" + std::to_string((int)customNjs) + "</u>" : std::to_string((int)customNjs));
    UpdateSpawnMovementData();
}
void IncreaseOffsetPause(){
    if(customOffset < 9.9) customOffset += 0.1f;
    OffsetTextPause.set(customOffset == defaultOffset ? "<u>" + std::to_string(customOffset).substr(0,customOffset < 0 ? 4 : 3) + "</u>" : std::to_string(customOffset).substr(0, customOffset < 0 ? 4 : 3));
    UpdateSpawnMovementData();
}
void DecreaseOffsetPause(){
    if(customOffset > -9.9) customOffset -= 0.1f;
    OffsetTextPause.set(customOffset == defaultOffset ? "<u>" + std::to_string(customOffset).substr(0,customOffset < 0 ? 4 : 3) + "</u>" : std::to_string(customOffset).substr(0, customOffset < 0 ? 4 : 3));
    UpdateSpawnMovementData();
}

void DestroyInMapUI(){
    NJSIncreasePause.destroy();
    NJSDecreasePause.destroy();
    OffsetDecreasePause.destroy();
    OffsetIncreasePause.destroy();
    njs.destroy();
    offset.destroy();
    NJSTextPause.destroy();
    OffsetTextPause.destroy();
}
