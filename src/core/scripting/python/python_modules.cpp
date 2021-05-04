#include "python_modules.h"

#include "../../global_dependencies.h"
#include "../../ecs/component/components/transform2D_component.h"
#include "../../input/input_manager.h"
#include "../../audio/audio_helper.h"

// ENGINE
PyObject* PythonModules::engine_exit(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EngineContext *engineContext = GD::GetContainer()->engineContext;
    int exitCode;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", engineExitKWList, &exitCode)) {
        engineContext->SetRunning(false);
        Py_RETURN_NONE;
    }
    return nullptr;
}

// AUDIO
PyObject* PythonModules::audio_play_music(PyObject *self, PyObject *args, PyObject *kwargs) {
    char *musicId;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "s", audioPlayMusicKWList, &musicId)) {
        AudioHelper::PlayMusic(std::string(musicId));
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::audio_stop_music(PyObject *self, PyObject *args) {
    AudioHelper::StopMusic();
    Py_RETURN_NONE;
}

PyObject* PythonModules::audio_set_music_volume(PyObject *self, PyObject *args, PyObject *kwargs) {
    int volume;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", audioSetVolumeKWList, &volume)) {
        AudioHelper::SetMusicVolume(volume);
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::audio_play_sound(PyObject *self, PyObject *args, PyObject *kwargs) {
    char *soundId;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "s", audioPlaySoundKWList, &soundId)) {
        AudioHelper::PlayMusic(std::string(soundId));
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::audio_set_sound_volume(PyObject *self, PyObject *args, PyObject *kwargs) {
    int volume;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", audioSetVolumeKWList, &volume)) {
        AudioHelper::SetSoundVolume(volume);
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::audio_set_all_volume(PyObject *self, PyObject *args, PyObject *kwargs) {
    int volume;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", audioSetVolumeKWList, &volume)) {
        AudioHelper::SetAllVolume(volume);
        Py_RETURN_NONE;
    }
    return nullptr;
}

// NODE2D
PyObject* PythonModules::node2D_get_position(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", nodeGetEntityKWList, &entity)) {
        Transform2DComponent transform2DComponent = entityComponentOrchestrator->GetComponent<Transform2DComponent>(entity);
        return Py_BuildValue("(ff)", transform2DComponent.position.x, transform2DComponent.position.y);
    }
    return nullptr;
}

PyObject* PythonModules::node2D_set_position(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    float x, y;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "iff", node2DUpdatePositionKWList, &entity, &x, &y)) {
        Transform2DComponent transform2DComponent = entityComponentOrchestrator->GetComponent<Transform2DComponent>(entity);
        transform2DComponent.position.x = x;
        transform2DComponent.position.y = y;
        entityComponentOrchestrator->UpdateComponent<Transform2DComponent>(entity, transform2DComponent);
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::node2D_add_to_position(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    float x, y;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "iff", node2DUpdatePositionKWList, &entity, &x, &y)) {
        Transform2DComponent transform2DComponent = entityComponentOrchestrator->GetComponent<Transform2DComponent>(entity);
        transform2DComponent.position.x += x;
        transform2DComponent.position.y += y;
        entityComponentOrchestrator->UpdateComponent<Transform2DComponent>(entity, transform2DComponent);
        Py_RETURN_NONE;
    }
    return nullptr;
}

// INPUT
PyObject* PythonModules::input_add_action(PyObject *self, PyObject *args, PyObject *kwargs) {
    static InputManager *inputManager = InputManager::GetInstance();
    char *pyActionName;
    char *pyValue;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "ss", inputAddActionKWList, &pyActionName, &pyValue)) {
        inputManager->AddAction(std::string(pyActionName), std::string(pyValue));
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::input_is_action_pressed(PyObject *self, PyObject *args, PyObject *kwargs) {
    static InputManager *inputManager = InputManager::GetInstance();
    char *pyActionName;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "s", inputActionCheckKWList, &pyActionName)) {
        if (inputManager->IsActionPressed(std::string(pyActionName))) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }
    return nullptr;
}

PyObject* PythonModules::input_is_action_just_pressed(PyObject *self, PyObject *args, PyObject *kwargs) {
    static InputManager *inputManager = InputManager::GetInstance();
    char *pyActionName;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "s", inputActionCheckKWList, &pyActionName)) {
        if (inputManager->IsActionJustPressed(std::string(pyActionName))) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }
    return nullptr;
}

PyObject* PythonModules::input_is_action_just_released(PyObject *self, PyObject *args, PyObject *kwargs) {
    static InputManager *inputManager = InputManager::GetInstance();
    char *pyActionName;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "s", inputActionCheckKWList, &pyActionName)) {
        if (inputManager->IsActionJustReleased(std::string(pyActionName))) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }
    return nullptr;
}
