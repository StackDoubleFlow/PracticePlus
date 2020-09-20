#include <unordered_set>

#include "../extern/beatsaber-hook/shared/utils/utils.h"
#include "../extern/beatsaber-hook/shared/utils/logging.hpp"
#include "../extern/modloader/shared/modloader.hpp"
#include "../extern/beatsaber-hook/shared/utils/typedefs.h"
#include "../extern/beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "../extern/beatsaber-hook/shared/utils/il2cpp-functions.hpp"
#include "../extern/custom-ui/shared/customui.hpp"

using namespace il2cpp_utils;
using namespace CustomUI;

extern Il2CppObject* _spawnController;

void log(std::string_view str);

extern Il2CppObject* sldv;

Il2CppObject* FindObjectsOfTypeAllFirstOrDefault(Il2CppReflectionType* Type);

void DestroyPracticeUI();
void DestroyInMapUI();

void CreatePracticeMenuUI(Il2CppObject* self);
void CreateInMapUI(Il2CppObject* self);
void UpdateSpeedShit();

extern float customNjs;
extern float customOffset;
extern float customSpeed;
extern float defaultNjs;
extern float defaultOffset;
extern float defaultSpeed;
extern float maxSongStartTime;

extern int diff;

extern bool inPracticeMode;

class CustomButton {
    public:
        Il2CppObject* gameObject = nullptr;
        Il2CppObject* TMP = nullptr;
        Il2CppObject* button = nullptr;
        Il2CppObject* buttonTransform = nullptr;
        Il2CppObject* parent = nullptr;
        Il2CppObject* parentTransform = nullptr;
        Il2CppObject* TMPLocalizer = nullptr;
        Vector3 sizeDelta = {0, 0, 0};
        Vector3 scale = {1.0f, 1.0f, 1.0f};
        Vector3 rotation = {0, 0, 0};
        float fontSize = 10.0f;
        std::string text = "Custom Button UI";
        function_ptr_t<void> onPress;
 
        bool isCreated = false;
 
        void setParentAndTransform(Il2CppObject* Obj, int parentedAmount) {
            parent = Obj;
 
            if(parentedAmount < 1) {
                parentedAmount = 1;
            }
            Il2CppObject* transform = *RunMethod(Obj, "get_transform");
            std::vector<Il2CppObject*> parents;
            Il2CppObject* firstParent = *RunMethod(transform, "GetParent");
            parents.push_back(firstParent);
            for(int i = 1; i < parentedAmount; i++) {
                Il2CppObject* otherParent = *RunMethod(parents[i-1], "GetParent");
                parents.push_back(otherParent);
            }
            parentTransform = parents[parents.size()-1];
        }
 
        void setParentTransform(Il2CppObject* Obj, int parentedAmount) {
            if(parentedAmount < 1) {
                parentedAmount = 1;
            }
            Il2CppObject* transform = *RunMethod(Obj, "get_transform");
            std::vector<Il2CppObject*> parents;
            Il2CppObject* firstParent = *RunMethod(transform, "GetParent");
            parents.push_back(firstParent);
            for(int i = 1; i < parentedAmount; i++) {
                Il2CppObject* otherParent = *RunMethod(parents[i-1], "GetParent");
                parents.push_back(otherParent);
            }
            parentTransform = parents[parents.size()-1];
        }
 
        void create() {
            if(!isCreated) {
                button = *il2cpp_utils::RunMethod("UnityEngine", "Object", "Instantiate", parent);
                buttonTransform = *il2cpp_utils::RunMethod(button, "get_transform");
                il2cpp_utils::RunMethod(buttonTransform, "SetParent", parentTransform);
                il2cpp_utils::RunMethod(buttonTransform, "set_localScale", scale);
                il2cpp_utils::RunMethod(buttonTransform, "set_localPosition", sizeDelta);
                gameObject = *il2cpp_utils::RunMethod(button, "get_gameObject");
                TMP = *il2cpp_utils::RunMethod(gameObject, "GetComponentInChildren", il2cpp_utils::GetSystemType("TMPro", "TextMeshProUGUI"));
                TMPLocalizer = *RunMethod<Il2CppObject*>(gameObject, "GetComponentInChildren", GetSystemType("Polyglot", "LocalizedTextMeshProUGUI"));
                RunMethod("UnityEngine", "Object", "Destroy", TMPLocalizer);
                auto* rectTransform = *RunMethod(TMP, "get_rectTransform");
                il2cpp_utils::RunMethod(TMP, "set_text", il2cpp_utils::createcsstr(text));
                il2cpp_utils::RunMethod(TMP, "set_fontSize", fontSize);
                Il2CppObject* onClick = *il2cpp_utils::GetPropertyValue(button, "onClick");
                auto actionToRun = il2cpp_utils::MakeAction(il2cpp_functions::class_get_type(il2cpp_utils::GetClassFromName("UnityEngine.Events", "UnityAction")), (Il2CppObject*)nullptr, onPress);
                il2cpp_utils::RunMethod(onClick, "AddListener", actionToRun);
                isCreated = true;
            } else {
                log("Already created.");
            }
        }
 
        void setText(std::string newText) {
            RunMethod(TMP, "SetText", createcsstr(newText));
        }
 
        void setActive(bool isActive) {
            RunMethod(gameObject, "SetActive", isActive);
        }
 
        void setPos(Vector3 pos) {//Doesnt work yet, work on it more later
            il2cpp_utils::RunMethod(buttonTransform, "set_localPosition", pos);
        }
 
        void destroy() {
            if(gameObject != nullptr) {
                RunMethod("UnityEngine", "Object", "Destroy", gameObject);
                gameObject = nullptr;
                TMP = nullptr;
                parentTransform = nullptr;
                parent = nullptr;
                TMPLocalizer = nullptr;
                isCreated = false;
            } else {
                log("Already destroyed.");
            }
        }
};



