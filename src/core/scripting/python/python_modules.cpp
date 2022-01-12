#include "python_modules.h"

#include "../../global_dependencies.h"
#include "python_cache.h"
#include "../../ecs/component/components/transform2D_component.h"
#include "../../input/input_manager.h"
#include "../../audio/audio_helper.h"
#include "../../audio/audio_stream_helper.h"
#include "../../utils/helper.h"
#include "../../signal_manager.h"
#include "../../ecs/system/systems/collision_entity_system.h"
#include "../../ecs/component/components/transform3D_component.h"
#include "../../ecs/component/components/texture_cube_component.h"
#include "../../ecs/component/components/light3D_component.h"
#include "../../ecs/system/systems/timer_entity_system.h"
#include "../../ecs/system/systems/text_rendering_entity_system.h"

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

PyObject* PythonModules::engine_get_fps(PyObject *self, PyObject *args) {
    static EngineContext *engineContext = GD::GetContainer()->engineContext;
    return PyLong_FromLong(engineContext->GetFPS());
}

// AUDIO
PyObject* PythonModules::audio_play_music(PyObject *self, PyObject *args, PyObject *kwargs) {
    char *musicId;
    bool musicLoops;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "sb", audioPlayMusicKWList, &musicId, &musicLoops)) {
        AudioHelper::PlayMusic(std::string(musicId), musicLoops);
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
        AudioHelper::PlaySound(std::string(soundId));
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

// AUDIO STREAM
PyObject* PythonModules::audio_stream_get(PyObject* self, PyObject* args, PyObject* kwargs) {
    static AssetManager *assetManager = GD::GetContainer()->assetManager;
    char *audioStreamUId;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "s", audioStreamGetKWList, &audioStreamUId)) {
        const std::string& uid = std::string(audioStreamUId);
        if (assetManager->HasAudioStream(uid)) {
            AudioStream* audioStream = assetManager->GetAudioStream(uid);
            return Py_BuildValue("(ffb)",
                                 audioStream->GetPitch(),
                                 audioStream->GetGain(),
                                 audioStream->DoesLoop());
        }
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::audio_stream_set_pitch(PyObject* self, PyObject* args, PyObject* kwargs) {
    static AssetManager *assetManager = GD::GetContainer()->assetManager;
    char *audioStreamUId;
    float audioPitch;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "sf", audioStreamSetPitchKWList, &audioStreamUId, &audioPitch)) {
        const std::string& uid = std::string(audioStreamUId);
        if (assetManager->HasAudioStream(uid)) {
            AudioStream* audioStream = assetManager->GetAudioStream(uid);
            audioStream->SetPitch(audioPitch);
        }
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::audio_stream_set_gain(PyObject* self, PyObject* args, PyObject* kwargs) {
    static AssetManager *assetManager = GD::GetContainer()->assetManager;
    char *audioStreamUId;
    float audioGain;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "sf", audioStreamSetGainKWList, &audioStreamUId, &audioGain)) {
        const std::string& uid = std::string(audioStreamUId);
        if (assetManager->HasAudioStream(uid)) {
            AudioStream* audioStream = assetManager->GetAudioStream(uid);
            audioStream->SetGain(audioGain);
        }
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::audio_stream_set_loops(PyObject* self, PyObject* args, PyObject* kwargs) {
    static AssetManager *assetManager = GD::GetContainer()->assetManager;
    char *audioStreamUId;
    bool audioLoops;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "sb", audioStreamSetLoopsKWList, &audioStreamUId, &audioLoops)) {
        const std::string& uid = std::string(audioStreamUId);
        if (assetManager->HasAudioStream(uid)) {
            AudioStream* audioStream = assetManager->GetAudioStream(uid);
            audioStream->SetLoops(audioLoops);
        }
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::audio_stream_play(PyObject* self, PyObject* args, PyObject* kwargs) {
    static AssetManager *assetManager = GD::GetContainer()->assetManager;
    char *audioStreamUId;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "s", audioStreamGetKWList, &audioStreamUId)) {
        const std::string& uid = std::string(audioStreamUId);
        if (assetManager->HasAudioStream(uid)) {
            AudioStream* audioStream = assetManager->GetAudioStream(uid);
            audioStream->Play();
        }
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::audio_stream_stop(PyObject* self, PyObject* args, PyObject* kwargs) {
    static AssetManager *assetManager = GD::GetContainer()->assetManager;
    char *audioStreamUId;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "s", audioStreamGetKWList, &audioStreamUId)) {
        const std::string& uid = std::string(audioStreamUId);
        if (assetManager->HasAudioStream(uid)) {
            AudioStream* audioStream = assetManager->GetAudioStream(uid);
            audioStream->Stop();
        }
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::audio_stream_is_playing(PyObject* self, PyObject* args, PyObject* kwargs) {
    static AssetManager *assetManager = GD::GetContainer()->assetManager;
    char *audioStreamUId;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "s", audioStreamGetKWList, &audioStreamUId)) {
        const std::string& uid = std::string(audioStreamUId);
        if (assetManager->HasAudioStream(uid)) {
            AudioStream* audioStream = assetManager->GetAudioStream(uid);
            if (audioStream->IsPlaying()) {
                Py_RETURN_TRUE;
            }
        }
        Py_RETURN_FALSE;
    }
    return nullptr;
}

// CAMERA 2D
PyObject* PythonModules::camera2d_get_zoom(PyObject *self, PyObject *args) {
    static CameraManager *cameraManager = GD::GetContainer()->cameraManager;
    Camera2D camera = cameraManager->GetCurrentCamera2D();
    return Py_BuildValue("(ff)", camera.zoom.x, camera.zoom.y);
}

PyObject* PythonModules::camera2d_set_zoom(PyObject *self, PyObject *args, PyObject *kwargs) {
    static CameraManager *cameraManager = GD::GetContainer()->cameraManager;
    float x, y;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "ff", camera2dVector2SetKWList, &x, &y)) {
        Camera2D camera = cameraManager->GetCurrentCamera2D();
        camera.zoom = Vector2(x, y);
        cameraManager->UpdateCurrentCamera2D(camera);
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::camera2d_get_viewport_position(PyObject *self, PyObject *args) {
    static CameraManager *cameraManager = GD::GetContainer()->cameraManager;
    Camera2D camera = cameraManager->GetCurrentCamera2D();
    return Py_BuildValue("(ff)", camera.viewport.x, camera.viewport.y);
}

PyObject* PythonModules::camera2d_set_viewport_position(PyObject *self, PyObject *args, PyObject *kwargs) {
    static CameraManager *cameraManager = GD::GetContainer()->cameraManager;
    float x, y;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "ff", camera2dVector2SetKWList, &x, &y)) {
        Camera2D camera = cameraManager->GetCurrentCamera2D();
        camera.viewport.x = Helper::Clamp(x, camera.boundary.x, camera.boundary.w);
        camera.viewport.y = Helper::Clamp(y, camera.boundary.y, camera.boundary.h);
        cameraManager->UpdateCurrentCamera2D(camera);
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::camera2d_get_offset(PyObject *self, PyObject *args) {
    static CameraManager *cameraManager = GD::GetContainer()->cameraManager;
    Camera2D camera = cameraManager->GetCurrentCamera2D();
    return Py_BuildValue("(ff)", camera.offset.x, camera.offset.y);
}

PyObject* PythonModules::camera2d_set_offset(PyObject *self, PyObject *args, PyObject *kwargs) {
    static CameraManager *cameraManager = GD::GetContainer()->cameraManager;
    float x, y;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "ff", camera2dVector2SetKWList, &x, &y)) {
        Camera2D camera = cameraManager->GetCurrentCamera2D();
        camera.offset = Vector2(x, y);
        cameraManager->UpdateCurrentCamera2D(camera);
        Py_RETURN_NONE;
    }
    return nullptr;
}

// CAMERA 3D
PyObject* PythonModules::camera3d_move_left(PyObject *self, PyObject *args, PyObject *kwargs) {
    static CameraManager *cameraManager = GD::GetContainer()->cameraManager;
    float speed;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "f", camera3dMoveKWList, &speed)) {
        Camera3D camera = cameraManager->GetCurrentCamera3D();
        camera.position -= glm::normalize(glm::cross(camera.front.ToGLM(), camera.up.ToGLM())) * speed;
        cameraManager->UpdateCurrentCamera3D(camera);
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::camera3d_move_right(PyObject *self, PyObject *args, PyObject *kwargs) {
    static CameraManager *cameraManager = GD::GetContainer()->cameraManager;
    float speed;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "f", camera3dMoveKWList, &speed)) {
        Camera3D camera = cameraManager->GetCurrentCamera3D();
        camera.position += glm::normalize(glm::cross(camera.front.ToGLM(), camera.up.ToGLM())) * speed;
        cameraManager->UpdateCurrentCamera3D(camera);
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::camera3d_move_up(PyObject *self, PyObject *args, PyObject *kwargs) {
    static CameraManager *cameraManager = GD::GetContainer()->cameraManager;
    float speed;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "f", camera3dMoveKWList, &speed)) {
        Camera3D camera = cameraManager->GetCurrentCamera3D();
        camera.position += camera.front * speed;
        cameraManager->UpdateCurrentCamera3D(camera);
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::camera3d_move_down(PyObject *self, PyObject *args, PyObject *kwargs) {
    static CameraManager *cameraManager = GD::GetContainer()->cameraManager;
    float speed;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "f", camera3dMoveKWList, &speed)) {
        Camera3D camera = cameraManager->GetCurrentCamera3D();
        camera.position -= camera.front * speed;
        cameraManager->UpdateCurrentCamera3D(camera);
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::camera3d_add_yaw(PyObject *self, PyObject *args, PyObject *kwargs) {
    static CameraManager *cameraManager = GD::GetContainer()->cameraManager;
    float yaw;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "f", camera3dAddYawKWList, &yaw)) {
        Camera3D camera = cameraManager->GetCurrentCamera3D();
        camera.yaw += yaw;
        camera.front.x = cos(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch));
        camera.front.y = sin(glm::radians(camera.pitch));
        camera.front.z = sin(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch));
        camera.front.Normalize();
        cameraManager->UpdateCurrentCamera3D(camera);
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::camera3d_add_pitch(PyObject *self, PyObject *args, PyObject *kwargs) {
    static CameraManager *cameraManager = GD::GetContainer()->cameraManager;
    float pitch;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "f", camera3dAddPitchKWList, &pitch)) {
        Camera3D camera = cameraManager->GetCurrentCamera3D();
        if (pitch > 89.0f) {
            pitch = 89.0f;
        }
        if (pitch < -89.0f) {
            pitch = -89.0f;
        }
        camera.pitch += pitch;
        camera.front.x = cos(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch));
        camera.front.y = sin(glm::radians(camera.pitch));
        camera.front.z = sin(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch));
        camera.front.Normalize();
        cameraManager->UpdateCurrentCamera3D(camera);
        Py_RETURN_NONE;
    }
    return nullptr;
}

// NODE
PyObject* PythonModules::node_new(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    static PythonCache *pythonCache = PythonCache::GetInstance();
    static ComponentManager *componentManager = GD::GetContainer()->componentManager;
    static EntityManager *entityManager = GD::GetContainer()->entityManager;
    static AssetManager *assetManager = GD::GetContainer()->assetManager;
    static TimerManager *timerManager = TimerManager::GetInstance();
    char *pyClassPath;
    char *pyClassName;
    char *pyNodeType;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "sss", nodeNewKWList, &pyClassPath, &pyClassName, &pyNodeType)) {
        SceneNode sceneNode = SceneNode{.entity = entityComponentOrchestrator->CreateEntity()};

        componentManager->AddComponent<NodeComponent>(sceneNode.entity, NodeComponent{
            .type = NodeTypeHelper::GetNodeTypeInt(std::string(pyNodeType)),
            .name = std::string(pyClassName)
        });

        NodeComponent nodeComponent = componentManager->GetComponent<NodeComponent>(sceneNode.entity);
        NodeTypeInheritance nodeTypeInheritance = NodeTypeHelper::GetNodeTypeInheritanceInt(nodeComponent.type);

        // TODO: Put this logic into a function
        // TODO: Add proper logic for component defaults
        if ((NodeType_TIMER & nodeTypeInheritance) == NodeType_TIMER) {
            const Uint32 defaultTimerWaitTime = 1000;
            const bool defaultTimerLoops = false;
            componentManager->AddComponent<TimerComponent>(sceneNode.entity, TimerComponent{
                .timer = timerManager->GenerateTimer(sceneNode.entity, defaultTimerWaitTime, defaultTimerLoops)
            });
        }

        if ((NodeType_NODE2D & nodeTypeInheritance) == NodeType_NODE2D) {
            componentManager->AddComponent<Transform2DComponent>(sceneNode.entity, Transform2DComponent{});
            auto signature = entityManager->GetSignature(sceneNode.entity);
            signature.set(componentManager->GetComponentType<Transform2DComponent>(), true);
            entityManager->SetSignature(sceneNode.entity, signature);
        }

        if ((NodeTypeInheritance_SPRITE & nodeTypeInheritance) == NodeTypeInheritance_SPRITE) {
            componentManager->AddComponent<SpriteComponent>(sceneNode.entity, SpriteComponent{});
            auto signature = entityManager->GetSignature(sceneNode.entity);
            signature.set(componentManager->GetComponentType<SpriteComponent>(), true);
            entityManager->SetSignature(sceneNode.entity, signature);
        }

        if ((NodeTypeInheritance_ANIMATED_SPRITE & nodeTypeInheritance) == NodeTypeInheritance_ANIMATED_SPRITE) {
            componentManager->AddComponent<AnimatedSpriteComponent>(sceneNode.entity, AnimatedSpriteComponent{});
            auto signature = entityManager->GetSignature(sceneNode.entity);
            signature.set(componentManager->GetComponentType<AnimatedSpriteComponent>(), true);
            entityManager->SetSignature(sceneNode.entity, signature);
        }

        if ((NodeTypeInheritance_TEXT_LABEL & nodeTypeInheritance) == NodeTypeInheritance_TEXT_LABEL) {
            TextLabelComponent textLabelComponent = TextLabelComponent{
                .text = "",
                .font = assetManager->GetFont(DEFAULT_FONT_ASSET_ID)
            };
            assert(textLabelComponent.font != nullptr && "Default font for text label is NULL!");
            componentManager->AddComponent<TextLabelComponent>(sceneNode.entity, textLabelComponent);
            auto signature = entityManager->GetSignature(sceneNode.entity);
            signature.set(componentManager->GetComponentType<TextLabelComponent>(), true);
            entityManager->SetSignature(sceneNode.entity, signature);
        }

        if ((NodeTypeInheritance_COLLISION_SHAPE2D & nodeTypeInheritance) == NodeTypeInheritance_COLLISION_SHAPE2D) {
            componentManager->AddComponent<ColliderComponent>(sceneNode.entity, ColliderComponent{.collider = Rect2(), .collisionExceptions = { sceneNode.entity }});
            auto signature = entityManager->GetSignature(sceneNode.entity);
            signature.set(componentManager->GetComponentType<ColliderComponent>(), true);
            entityManager->SetSignature(sceneNode.entity, signature);
        }

        if ((NodeTypeInheritance_SPATIAL & nodeTypeInheritance) == NodeTypeInheritance_SPATIAL) {
            componentManager->AddComponent<Transform3DComponent>(sceneNode.entity, Transform3DComponent{});
            auto signature = entityManager->GetSignature(sceneNode.entity);
            signature.set(componentManager->GetComponentType<Transform3DComponent>(), true);
            entityManager->SetSignature(sceneNode.entity, signature);
        }

        if ((NodeTypeInheritance_TEXTURE_CUBE & nodeTypeInheritance) == NodeTypeInheritance_TEXTURE_CUBE) {
            componentManager->AddComponent<TextureCubeComponent>(sceneNode.entity, TextureCubeComponent{});
            auto signature = entityManager->GetSignature(sceneNode.entity);
            signature.set(componentManager->GetComponentType<TextureCubeComponent>(), true);
            entityManager->SetSignature(sceneNode.entity, signature);
        }

        if ((NodeTypeInheritance_DIRECTIONAL_LIGHT & nodeTypeInheritance) == NodeTypeInheritance_DIRECTIONAL_LIGHT) {
            componentManager->AddComponent<DirectionalLightComponent>(sceneNode.entity, DirectionalLightComponent{});
            auto signature = entityManager->GetSignature(sceneNode.entity);
            signature.set(componentManager->GetComponentType<DirectionalLightComponent>(), true);
            entityManager->SetSignature(sceneNode.entity, signature);
        }

        if ((NodeTypeInheritance_POINT_LIGHT & nodeTypeInheritance) == NodeTypeInheritance_POINT_LIGHT) {
            componentManager->AddComponent<PointLightComponent>(sceneNode.entity, PointLightComponent{});
            auto signature = entityManager->GetSignature(sceneNode.entity);
            signature.set(componentManager->GetComponentType<PointLightComponent>(), true);
            entityManager->SetSignature(sceneNode.entity, signature);
        }

        if ((NodeTypeInheritance_SPOT_LIGHT & nodeTypeInheritance) == NodeTypeInheritance_SPOT_LIGHT) {
            componentManager->AddComponent<SpotLightComponent>(sceneNode.entity, SpotLightComponent{});
            auto signature = entityManager->GetSignature(sceneNode.entity);
            signature.set(componentManager->GetComponentType<SpotLightComponent>(), true);
            entityManager->SetSignature(sceneNode.entity, signature);
        }

        if (NodeTypeHelper::IsNameDefaultNodeClass(std::string(pyClassName))) {
            pythonCache->CreateClassInstance(std::string(pyClassPath), std::string(pyClassName), sceneNode.entity);
        } else {
            componentManager->AddComponent(sceneNode.entity, ScriptableClassComponent{
                .classPath = std::string(pyClassPath),
                .className = std::string(pyClassName)
            });
            auto scriptClassSignature = entityManager->GetSignature(sceneNode.entity);
            scriptClassSignature.set(componentManager->GetComponentType<ScriptableClassComponent>(), true);
            entityManager->SetSignature(sceneNode.entity, scriptClassSignature);

            entityComponentOrchestrator->NewEntity(sceneNode);
        }

        if (pythonCache->HasActiveInstance(sceneNode.entity)) {
            CPyObject &pClassInstance = pythonCache->GetClassInstance(sceneNode.entity);
            pClassInstance.AddRef();
            return pClassInstance;
        }
        Logger::GetInstance()->Error("failed to add new python instance");
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::node_add_child(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity parentEntity;
    Entity childEntity;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "ii", nodeAddChildKWList, &parentEntity, &childEntity)) {
        entityComponentOrchestrator->NewEntityAddChild(parentEntity, childEntity);
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::node_get_node(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    static PythonCache *pythonCache = PythonCache::GetInstance();
    static ComponentManager *componentManager = GD::GetContainer()->componentManager;
    char *pyNodeName;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "s", nodeGetNodeKWList, &pyNodeName)) {
        Entity entity = entityComponentOrchestrator->GetEntityFromNodeName(std::string(pyNodeName));
        if (entity != NULL_ENTITY) {
            if (pythonCache->HasActiveInstance(entity)) {
                CPyObject &pClassInstance = pythonCache->GetClassInstance(entity);
                pClassInstance.AddRef();
                return pClassInstance;
            }
            // Creates new instance on script side if active script instance of entity doesn't exist
            NodeComponent nodeComponent = componentManager->GetComponent<NodeComponent>(entity);
            const std::string &nodeTypeString = NodeTypeHelper::GetNodeTypeString(nodeComponent.type);
            return Py_BuildValue("(si)", nodeTypeString.c_str(), entity);
        }
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::node_queue_deletion(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", nodeGetEntityKWList, &entity)) {
        entityComponentOrchestrator->QueueEntityForDeletion(entity);
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::node_signal_connect(PyObject *self, PyObject *args, PyObject *kwargs) {
    static SignalManager *signalManager = SignalManager::GetInstance();
    Entity entity;
    char *pySignalId;
    Entity subscriberEntity;
    char *pyFunctionName;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "isis", nodeSignalConnectKWList, &entity, &pySignalId, &subscriberEntity, &pyFunctionName)) {
        signalManager->SubscribeToSignal(entity, std::string(pySignalId), subscriberEntity, std::string(pyFunctionName));
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::node_signal_create(PyObject *self, PyObject *args, PyObject *kwargs) {
    static SignalManager *signalManager = SignalManager::GetInstance();
    Entity entity;
    char *pySignalId;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "is", nodeSignalCreateKWList, &entity, &pySignalId)) {
        signalManager->CreateSignal(entity, std::string(pySignalId));
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::node_signal_emit(PyObject *self, PyObject *args, PyObject *kwargs) {
    static SignalManager *signalManager = SignalManager::GetInstance();
    Entity entity;
    char *pySignalId;
    PyObject *pyObject = nullptr;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "isO", nodeSignalEmitKWList, &entity, &pySignalId, &pyObject)) {
        signalManager->EmitSignal(entity, std::string(pySignalId), SignalArguments{.pyArgs = pyObject});
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::node_get_name(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", nodeGetEntityKWList, &entity)) {
        NodeComponent nodeComponent = entityComponentOrchestrator->GetComponent<NodeComponent>(entity);
        return Py_BuildValue("s", nodeComponent.name.c_str());
    }
    return nullptr;
}

PyObject* PythonModules::node_get_tags(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", nodeGetEntityKWList, &entity)) {
        NodeComponent nodeComponent = entityComponentOrchestrator->GetComponent<NodeComponent>(entity);
        CPyObject pTagList = PyList_New(0);
        pTagList.AddRef();
        assert(pTagList != nullptr && "node list empty!");
        for (const std::string &tagText : nodeComponent.tags) {
            if (PyList_Append(pTagList, Py_BuildValue("s", tagText.c_str())) == -1) {
                PyErr_Print();
            }
        }
        return pTagList;
    }
    return nullptr;
}

PyObject* PythonModules::node_set_tags(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    static EntitySystemManager* entitySystemManager = EntitySystemManager::GetInstance();
    Entity entity;
    PyObject *pyObject = nullptr;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "iO", nodeSetTagsKWList, &entity, &pyObject)) {
        NodeComponent nodeComponent = entityComponentOrchestrator->GetComponent<NodeComponent>(entity);
        std::vector<std::string> nodeTags = {};
        for (int i = 0; i < PyList_Size(pyObject); i++) {
            CPyObject listItem = PyList_GetItem(pyObject, i);
            listItem.AddRef();
            const std::string &newTag = std::string(PyUnicode_AsUTF8(listItem));
            nodeTags.emplace_back(newTag);
        }
        entitySystemManager->OnEntityTagsUpdatedSystemsHook(entity, nodeComponent.tags, nodeTags);
        nodeComponent.tags = nodeTags;
        entityComponentOrchestrator->UpdateComponent<NodeComponent>(entity, nodeComponent);
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::node_show(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", nodeGetEntityKWList, &entity)) {
        NodeComponent nodeComponent = entityComponentOrchestrator->GetComponent<NodeComponent>(entity);
        if (!nodeComponent.visible) {
            if (entityComponentOrchestrator->HasComponent<SpriteComponent>(entity)) {
                entityComponentOrchestrator->EnableComponent<SpriteComponent>(entity);
            }
            if (entityComponentOrchestrator->HasComponent<AnimatedSpriteComponent>(entity)) {
                entityComponentOrchestrator->EnableComponent<AnimatedSpriteComponent>(entity);
            }
            if (entityComponentOrchestrator->HasComponent<TextLabelComponent>(entity)) {
                entityComponentOrchestrator->EnableComponent<TextLabelComponent>(entity);
            }
            if (entityComponentOrchestrator->HasComponent<TextureCubeComponent>(entity)) {
                entityComponentOrchestrator->EnableComponent<TextureCubeComponent>(entity);
            }
            nodeComponent.visible = true;
            entityComponentOrchestrator->UpdateComponent<NodeComponent>(entity, nodeComponent);
        }
    }
    Py_RETURN_NONE;
}

PyObject* PythonModules::node_hide(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", nodeGetEntityKWList, &entity)) {
        NodeComponent nodeComponent = entityComponentOrchestrator->GetComponent<NodeComponent>(entity);
        if (nodeComponent.visible) {
            if (entityComponentOrchestrator->HasComponent<SpriteComponent>(entity)) {
                entityComponentOrchestrator->DisableComponent<SpriteComponent>(entity);
            }
            if (entityComponentOrchestrator->HasComponent<AnimatedSpriteComponent>(entity)) {
                entityComponentOrchestrator->DisableComponent<AnimatedSpriteComponent>(entity);
            }
            if (entityComponentOrchestrator->HasComponent<TextLabelComponent>(entity)) {
                entityComponentOrchestrator->DisableComponent<TextLabelComponent>(entity);
            }
            if (entityComponentOrchestrator->HasComponent<TextureCubeComponent>(entity)) {
                entityComponentOrchestrator->DisableComponent<TextureCubeComponent>(entity);
            }
            nodeComponent.visible = false;
            entityComponentOrchestrator->UpdateComponent<NodeComponent>(entity, nodeComponent);
        }
    }
    Py_RETURN_NONE;
}

PyObject* PythonModules::node_is_visible(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", nodeGetEntityKWList, &entity)) {
        NodeComponent nodeComponent = entityComponentOrchestrator->GetComponent<NodeComponent>(entity);
        if (nodeComponent.visible) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }
    return nullptr;
}

PyObject* PythonModules::node_get_parent(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    static PythonCache *pythonCache = PythonCache::GetInstance();
    Entity entity;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", nodeGetEntityKWList, &entity)) {
        Entity parentEntity = entityComponentOrchestrator->GetEntityParent(entity);
        if (parentEntity != NULL_ENTITY) {
            if (pythonCache->HasActiveInstance(parentEntity)) {
                CPyObject& instance = pythonCache->GetClassInstance(parentEntity);
                instance.AddRef();
                return Py_BuildValue("O", instance.GetObj());
            } else {
                NodeComponent nodeComponent = entityComponentOrchestrator->GetComponent<NodeComponent>(parentEntity);
                const std::string &nodeTypeString = NodeTypeHelper::GetNodeTypeString(nodeComponent.type);
                return Py_BuildValue("(si)", nodeTypeString.c_str(), parentEntity);
            }
        }
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::node_get_children(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    static PythonCache *pythonCache = PythonCache::GetInstance();
    Entity entity;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", nodeGetEntityKWList, &entity)) {
        CPyObject pCollidedNodesList = PyList_New(0);
        pCollidedNodesList.AddRef();
        assert(pCollidedNodesList != nullptr && "node list empty!");
        for (Entity collidedEntity : entityComponentOrchestrator->GetEntityChildren(entity)) {
            if (!entityComponentOrchestrator->IsEntityQueuedForDeletion(collidedEntity)) {
                if (pythonCache->HasActiveInstance(collidedEntity)) {
                    CPyObject &pCollidedClassInstance = pythonCache->GetClassInstance(collidedEntity);
                    pCollidedClassInstance.AddRef();
                    if (PyList_Append(pCollidedNodesList, pCollidedClassInstance) == -1) {
                        PyErr_Print();
                    }
                } else {
                    NodeComponent nodeComponent = entityComponentOrchestrator->GetComponent<NodeComponent>(collidedEntity);
                    const std::string &nodeTypeString = NodeTypeHelper::GetNodeTypeString(nodeComponent.type);
                    if (PyList_Append(pCollidedNodesList, Py_BuildValue("(si)", nodeTypeString.c_str(), collidedEntity)) == -1) {
                        Logger::GetInstance()->Error("Error appending list");
                        PyErr_Print();
                    }
                }
            }
        }
        return pCollidedNodesList;
    }
    return nullptr;
}

// TIMER
PyObject* PythonModules::timer_start(PyObject *self, PyObject *args, PyObject *kwargs) {
    static TimerManager *timerManager = TimerManager::GetInstance();
    Entity entity;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", nodeGetEntityKWList, &entity)) {
        timerManager->StartTimer(entity);
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::timer_stop(PyObject *self, PyObject *args, PyObject *kwargs) {
    static TimerManager *timerManager = TimerManager::GetInstance();
    Entity entity;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", nodeGetEntityKWList, &entity)) {
        timerManager->StopTimer(entity);
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::timer_pause(PyObject *self, PyObject *args, PyObject *kwargs) {
    static TimerManager *timerManager = TimerManager::GetInstance();
    Entity entity;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", nodeGetEntityKWList, &entity)) {
        timerManager->PauseTimer(entity);
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::timer_resume(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    static TimerManager *timerManager = TimerManager::GetInstance();
    Entity entity;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", nodeGetEntityKWList, &entity)) {
        timerManager->ResumeTimer(entity);
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::timer_get_wait_time(PyObject *self, PyObject *args, PyObject *kwargs) {
    static TimerManager *timerManager = TimerManager::GetInstance();
    Entity entity;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", nodeGetEntityKWList, &entity)) {
        return Py_BuildValue("f", timerManager->GetTimerWaitTime(entity));
    }
    return nullptr;
}

PyObject* PythonModules::timer_set_wait_time(PyObject *self, PyObject *args, PyObject *kwargs) {
    static TimerManager *timerManager = TimerManager::GetInstance();
    Entity entity;
    float waitTime;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "if", timerSetWaitTimeKWList, &entity, &waitTime)) {
        timerManager->SetTimerWaitTime(entity, waitTime);
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::timer_get_time_left(PyObject *self, PyObject *args, PyObject *kwargs) {
    static TimerManager *timerManager = TimerManager::GetInstance();
    Entity entity;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", nodeGetEntityKWList, &entity)) {
        return Py_BuildValue("f", timerManager->GetTimerTimeLeft(entity));
    }
    return nullptr;
}

PyObject* PythonModules::timer_is_stopped(PyObject *self, PyObject *args, PyObject *kwargs) {
    static TimerManager *timerManager = TimerManager::GetInstance();
    Entity entity;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", nodeGetEntityKWList, &entity)) {
        if (timerManager->IsTimerStopped(entity)) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }
    return nullptr;
}

PyObject* PythonModules::timer_is_paused(PyObject *self, PyObject *args, PyObject *kwargs) {
    static TimerManager *timerManager = TimerManager::GetInstance();
    Entity entity;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", nodeGetEntityKWList, &entity)) {
        if (timerManager->IsTimerPaused(entity)) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }
    return nullptr;
}

PyObject* PythonModules::timer_set_loops(PyObject *self, PyObject *args, PyObject *kwargs) {
    static TimerManager *timerManager = TimerManager::GetInstance();
    Entity entity;
    bool loops;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "ib", timerSetLoopsKWList, &entity, &loops)) {
        timerManager->SetTimerLoops(entity, loops);
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::timer_get_loops(PyObject *self, PyObject *args, PyObject *kwargs) {
    static TimerManager *timerManager = TimerManager::GetInstance();
    Entity entity;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", nodeGetEntityKWList, &entity)) {
        if (timerManager->DoesTimerLoop(entity)) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
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

PyObject* PythonModules::node2D_get_rotation(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", nodeGetEntityKWList, &entity)) {
        Transform2DComponent transform2DComponent = entityComponentOrchestrator->GetComponent<Transform2DComponent>(entity);
        return Py_BuildValue("f", transform2DComponent.rotation);
    }
    return nullptr;
}

PyObject* PythonModules::node2D_set_rotation(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    float rotation;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "if", node2DSetRotationKWList, &entity, &rotation)) {
        Transform2DComponent transform2DComponent = entityComponentOrchestrator->GetComponent<Transform2DComponent>(entity);
        transform2DComponent.rotation = rotation;
        entityComponentOrchestrator->UpdateComponent<Transform2DComponent>(entity, transform2DComponent);
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::node2D_get_z_index(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", nodeGetEntityKWList, &entity)) {
        Transform2DComponent transform2DComponent = entityComponentOrchestrator->GetComponent<Transform2DComponent>(entity);
        return Py_BuildValue("i", transform2DComponent.zIndex);
    }
    return nullptr;
}

PyObject* PythonModules::node2D_set_z_index(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    int zIndex;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "ii", node2DSetZIndexKWList, &entity, &zIndex)) {
        Transform2DComponent transform2DComponent = entityComponentOrchestrator->GetComponent<Transform2DComponent>(entity);
        transform2DComponent.zIndex = zIndex;
        entityComponentOrchestrator->UpdateComponent<Transform2DComponent>(entity, transform2DComponent);
        Py_RETURN_NONE;
    }
    return nullptr;
}

// SPRITE
PyObject* PythonModules::sprite_get_flip_h(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", nodeGetEntityKWList, &entity)) {
        SpriteComponent spriteComponent = entityComponentOrchestrator->GetComponent<SpriteComponent>(entity);
        if (spriteComponent.flipX) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }
    return nullptr;
}

PyObject* PythonModules::sprite_set_flip_h(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    bool flipH;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "ib", spriteSetSpriteFlipHKWList, &entity, &flipH)) {
        SpriteComponent spriteComponent = entityComponentOrchestrator->GetComponent<SpriteComponent>(entity);
        spriteComponent.flipX = flipH;
        entityComponentOrchestrator->UpdateComponent<SpriteComponent>(entity, spriteComponent);
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::sprite_get_flip_v(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", nodeGetEntityKWList, &entity)) {
        SpriteComponent spriteComponent = entityComponentOrchestrator->GetComponent<SpriteComponent>(entity);
        if (spriteComponent.flipY) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }
    return nullptr;
}

PyObject* PythonModules::sprite_set_flip_v(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    bool flipV;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "ib", spriteSetSpriteFlipVKWList, &entity, &flipV)) {
        SpriteComponent spriteComponent = entityComponentOrchestrator->GetComponent<SpriteComponent>(entity);
        spriteComponent.flipY = flipV;
        entityComponentOrchestrator->UpdateComponent<SpriteComponent>(entity, spriteComponent);
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::sprite_get_modulate(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", nodeGetEntityKWList, &entity)) {
        SpriteComponent spriteComponent = entityComponentOrchestrator->GetComponent<SpriteComponent>(entity);
        return Py_BuildValue("(ffff)",
                             spriteComponent.modulate.r,
                             spriteComponent.modulate.g,
                             spriteComponent.modulate.b,
                             spriteComponent.modulate.a);
    }
    return nullptr;
}

PyObject* PythonModules::sprite_set_modulate(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    float red, green, blue, alpha;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "iffff", nodeSetColorKWList, &entity, &red, &green, &blue, &alpha)) {
        SpriteComponent spriteComponent = entityComponentOrchestrator->GetComponent<SpriteComponent>(entity);
        spriteComponent.modulate = Color(red, green, blue, alpha);
        entityComponentOrchestrator->UpdateComponent<SpriteComponent>(entity, spriteComponent);
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::sprite_get_texture(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", nodeGetEntityKWList, &entity)) {
        SpriteComponent spriteComponent = entityComponentOrchestrator->GetComponent<SpriteComponent>(entity);
        Texture *texture = spriteComponent.texture;
        if (texture == nullptr) {
            Py_RETURN_NONE;
        }
        return Py_BuildValue("(sssss)",
                             texture->GetFilePath().c_str(),
                             texture->GetWrapSString().c_str(),
                             texture->GetWrapTString().c_str(),
                             texture->GetFilterMinString().c_str(),
                             texture->GetFilterMagString().c_str());
    }
    return nullptr;
}

PyObject* PythonModules::sprite_set_texture(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    static AssetManager *assetManager = GD::GetContainer()->assetManager;
    Entity entity;
    char *pyFilePath;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "is", spriteSetTextureKWList, &entity, &pyFilePath)) {
        SpriteComponent spriteComponent = entityComponentOrchestrator->GetComponent<SpriteComponent>(entity);
        Texture *texture = assetManager->GetTexture(std::string(pyFilePath));
        spriteComponent.texture = texture;
        if (spriteComponent.drawSource == Rect2(0.0f, 0.0f, 0.0f, 0.0f)) {
            spriteComponent.drawSource = Rect2(0.0f, 0.0f, texture->GetWidth(), texture->GetHeight());
        }
        entityComponentOrchestrator->UpdateComponent<SpriteComponent>(entity, spriteComponent);
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::sprite_get_draw_source(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", nodeGetEntityKWList, &entity)) {
        SpriteComponent spriteComponent = entityComponentOrchestrator->GetComponent<SpriteComponent>(entity);
        return Py_BuildValue("(ffff)",
                             spriteComponent.drawSource.x,
                             spriteComponent.drawSource.y,
                             spriteComponent.drawSource.w,
                             spriteComponent.drawSource.h);
    }
    return nullptr;
}

PyObject* PythonModules::sprite_set_draw_source(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    float x;
    float y;
    float w;
    float h;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "iffff", spriteSetDrawSourceKWList, &entity, &x, &y, &w, &h)) {
        SpriteComponent spriteComponent = entityComponentOrchestrator->GetComponent<SpriteComponent>(entity);
        spriteComponent.drawSource = Rect2(x, y, w, h);
        entityComponentOrchestrator->UpdateComponent<SpriteComponent>(entity, spriteComponent);
        Py_RETURN_NONE;
    }
    return nullptr;
}

// ANIMATED_SPRITE
PyObject* PythonModules::animated_sprite_play(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    char *pyAnimationName;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "is", animatedSpriteAnimationUpdateKWList, &entity, &pyAnimationName)) {
        AnimatedSpriteComponent animatedSpriteComponent = entityComponentOrchestrator->GetComponent<AnimatedSpriteComponent>(entity);
        const std::string &animationName = std::string(pyAnimationName);
        if (animationName.empty()) {
            animatedSpriteComponent.isPlaying = true;
        } else if (animatedSpriteComponent.animations.count(animationName) > 0) {
            animatedSpriteComponent.isPlaying = true;
            animatedSpriteComponent.currentAnimation = animatedSpriteComponent.animations[animationName];
        }
        entityComponentOrchestrator->UpdateComponent<AnimatedSpriteComponent>(entity, animatedSpriteComponent);
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::animated_sprite_set_animation(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    char *pyAnimationName;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "is", animatedSpriteAnimationUpdateKWList, &entity, &pyAnimationName)) {
        AnimatedSpriteComponent animatedSpriteComponent = entityComponentOrchestrator->GetComponent<AnimatedSpriteComponent>(entity);
        const std::string &animationName = std::string(pyAnimationName);
        if (animatedSpriteComponent.animations.count(animationName) > 0) {
            animatedSpriteComponent.currentAnimation = animatedSpriteComponent.animations[animationName];
            entityComponentOrchestrator->UpdateComponent<AnimatedSpriteComponent>(entity, animatedSpriteComponent);
        }
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::animated_sprite_stop(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", nodeGetEntityKWList, &entity)) {
        AnimatedSpriteComponent animatedSpriteComponent = entityComponentOrchestrator->GetComponent<AnimatedSpriteComponent>(entity);
        animatedSpriteComponent.isPlaying = false;
        entityComponentOrchestrator->UpdateComponent<AnimatedSpriteComponent>(entity, animatedSpriteComponent);
        Py_RETURN_NONE;
    }
    return nullptr;
}

// TODO: Actually implement!
PyObject* PythonModules::animated_sprite_get_animations(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", nodeGetEntityKWList, &entity)) {
        AnimatedSpriteComponent animatedSpriteComponent = entityComponentOrchestrator->GetComponent<AnimatedSpriteComponent>(entity);
        CPyObject pTagList = PyList_New(0);
        pTagList.AddRef();
        return pTagList;
    }
    return nullptr;
}

PyObject* PythonModules::animated_sprite_set_animations(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    static AssetManager *assetManager = GD::GetContainer()->assetManager;
    Entity entity;
    PyObject *pyList = nullptr;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "iO", animatedSpriteSetAnimationsKWList, &entity, &pyList)) {
        AnimatedSpriteComponent animatedSpriteComponent = entityComponentOrchestrator->GetComponent<AnimatedSpriteComponent>(entity);
        animatedSpriteComponent.animations.clear();
        std::string firstAnimName;
        for (int i = 0; i < PyList_Size(pyList); i++) {
            CPyObject listTupleItem = PyList_GetItem(pyList, i);
            listTupleItem.AddRef();
            CPyObject pyAnimName = PyTuple_GetItem(listTupleItem, 0);
            pyAnimName.AddRef();
            CPyObject pyAnimSpeed = PyTuple_GetItem(listTupleItem, 1);
            pyAnimSpeed.AddRef();
            CPyObject pyAnimFrames = PyTuple_GetItem(listTupleItem, 2);
            pyAnimFrames.AddRef();
            const std::string& animName = std::string(PyUnicode_AsUTF8(pyAnimName));
            const int animSpeed = PyLong_AsLong(pyAnimSpeed);
            if (i == 0) {
                firstAnimName = animName;
            }
            std::map<unsigned int, AnimationFrame> animationFrames = {};
            for (int j = 0; j < PyList_Size(pyAnimFrames); j++) {
                CPyObject frameTupleItem = PyList_GetItem(pyAnimFrames, j);
                frameTupleItem.AddRef();
                CPyObject pyTextureFilePath = PyTuple_GetItem(frameTupleItem, 0);
                pyTextureFilePath.AddRef();
                CPyObject pyDrawSourceX = PyTuple_GetItem(frameTupleItem, 1);
                pyDrawSourceX.AddRef();
                CPyObject pyDrawSourceY = PyTuple_GetItem(frameTupleItem, 2);
                pyDrawSourceY.AddRef();
                CPyObject pyDrawSourceW = PyTuple_GetItem(frameTupleItem, 3);
                pyDrawSourceW.AddRef();
                CPyObject pyDrawSourceH = PyTuple_GetItem(frameTupleItem, 4);
                pyDrawSourceH.AddRef();
                CPyObject pyIndex = PyTuple_GetItem(frameTupleItem, 5);
                pyIndex.AddRef();
                const std::string& frameTextureFilePath = std::string(PyUnicode_AsUTF8(pyTextureFilePath));
                const float frameDrawSourceX = PyLong_AsLong(pyDrawSourceX);
                const float frameDrawSourceY = PyLong_AsLong(pyDrawSourceY);
                const float frameDrawSourceW = PyLong_AsLong(pyDrawSourceW);
                const float frameDrawSourceH = PyLong_AsLong(pyDrawSourceH);
                const int frameIndex = PyLong_AsLong(pyIndex);
                animationFrames.emplace(frameIndex, AnimationFrame{
                    assetManager->GetTexture(frameTextureFilePath),
                    Rect2(frameDrawSourceX, frameDrawSourceY, frameDrawSourceW, frameDrawSourceH),
                    frameIndex
                });
            }
            animatedSpriteComponent.animations.emplace(animName, Animation{
                animName, animSpeed, animationFrames, animationFrames.size()
            });
        }
        animatedSpriteComponent.currentFrameIndex = 0;
        if (animatedSpriteComponent.animations.size() > 0) {
            animatedSpriteComponent.currentAnimation = animatedSpriteComponent.animations[firstAnimName];
        }
        entityComponentOrchestrator->UpdateComponent<AnimatedSpriteComponent>(entity, animatedSpriteComponent);
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::animated_sprite_is_playing(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", nodeGetEntityKWList, &entity)) {
        AnimatedSpriteComponent animatedSpriteComponent = entityComponentOrchestrator->GetComponent<AnimatedSpriteComponent>(entity);
        if (animatedSpriteComponent.isPlaying) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }
    return nullptr;
}

PyObject* PythonModules::animated_sprite_get_modulate(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", nodeGetEntityKWList, &entity)) {
        AnimatedSpriteComponent animatedSpriteComponent = entityComponentOrchestrator->GetComponent<AnimatedSpriteComponent>(entity);
        return Py_BuildValue("(ffff)",
                             animatedSpriteComponent.modulate.r,
                             animatedSpriteComponent.modulate.g,
                             animatedSpriteComponent.modulate.b,
                             animatedSpriteComponent.modulate.a);
    }
    return nullptr;
}

PyObject* PythonModules::animated_sprite_set_modulate(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    float red, green, blue, alpha;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "iffff", nodeSetColorKWList, &entity, &red, &green, &blue, &alpha)) {
        AnimatedSpriteComponent animatedSpriteComponent = entityComponentOrchestrator->GetComponent<AnimatedSpriteComponent>(entity);
        animatedSpriteComponent.modulate = Color(red, green, blue, alpha);
        entityComponentOrchestrator->UpdateComponent<AnimatedSpriteComponent>(entity, animatedSpriteComponent);
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::animated_sprite_get_frame(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", nodeGetEntityKWList, &entity)) {
        AnimatedSpriteComponent animatedSpriteComponent = entityComponentOrchestrator->GetComponent<AnimatedSpriteComponent>(entity);
        return Py_BuildValue("i", animatedSpriteComponent.currentFrameIndex);
    }
    return nullptr;
}

PyObject* PythonModules::animated_sprite_set_frame(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    int animationFrame;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "ii", animatedSpriteSetFrameKWList, &entity, &animationFrame)) {
        AnimatedSpriteComponent animatedSpriteComponent = entityComponentOrchestrator->GetComponent<AnimatedSpriteComponent>(entity);
        animatedSpriteComponent.currentFrameIndex = animationFrame;
        entityComponentOrchestrator->UpdateComponent<AnimatedSpriteComponent>(entity, animatedSpriteComponent);
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::animated_sprite_get_animation_frames(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", nodeGetEntityKWList, &entity)) {
        AnimatedSpriteComponent animatedSpriteComponent = entityComponentOrchestrator->GetComponent<AnimatedSpriteComponent>(entity);
        return Py_BuildValue("i", animatedSpriteComponent.currentAnimation.frames);
    }
    return nullptr;
}

PyObject* PythonModules::animated_sprite_get_animation_speed(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", nodeGetEntityKWList, &entity)) {
        AnimatedSpriteComponent animatedSpriteComponent = entityComponentOrchestrator->GetComponent<AnimatedSpriteComponent>(entity);
        return Py_BuildValue("i", animatedSpriteComponent.currentAnimation.speed);
    }
    return nullptr;
}

PyObject* PythonModules::animated_sprite_get_flip_h(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", nodeGetEntityKWList, &entity)) {
        AnimatedSpriteComponent animatedSpriteComponent = entityComponentOrchestrator->GetComponent<AnimatedSpriteComponent>(entity);
        if (animatedSpriteComponent.flipX) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }
    return nullptr;
}

PyObject* PythonModules::animated_sprite_set_flip_h(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    bool flipH;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "ib", spriteSetSpriteFlipHKWList, &entity, &flipH)) {
        AnimatedSpriteComponent animatedSpriteComponent = entityComponentOrchestrator->GetComponent<AnimatedSpriteComponent>(entity);
        animatedSpriteComponent.flipX = flipH;
        entityComponentOrchestrator->UpdateComponent<AnimatedSpriteComponent>(entity, animatedSpriteComponent);
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::animated_sprite_get_flip_v(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", nodeGetEntityKWList, &entity)) {
        AnimatedSpriteComponent animatedSpriteComponent = entityComponentOrchestrator->GetComponent<AnimatedSpriteComponent>(entity);
        if (animatedSpriteComponent.flipY) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }
    return nullptr;
}

PyObject* PythonModules::animated_sprite_set_flip_v(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    bool flipV;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "ib", spriteSetSpriteFlipVKWList, &entity, &flipV)) {
        AnimatedSpriteComponent animatedSpriteComponent = entityComponentOrchestrator->GetComponent<AnimatedSpriteComponent>(entity);
        animatedSpriteComponent.flipY = flipV;
        entityComponentOrchestrator->UpdateComponent<AnimatedSpriteComponent>(entity, animatedSpriteComponent);
        Py_RETURN_NONE;
    }
    return nullptr;
}

// TEXT_LABEL
PyObject* PythonModules::text_label_get_text(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", nodeGetEntityKWList, &entity)) {
        TextLabelComponent textLabelComponent = entityComponentOrchestrator->GetComponent<TextLabelComponent>(entity);
        return Py_BuildValue("s", textLabelComponent.text.c_str());
    }
    return nullptr;
}

PyObject* PythonModules::text_label_set_text(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    static TextRenderingEntitySystem* textRenderingEntitySystem = entityComponentOrchestrator->GetSystem<TextRenderingEntitySystem>();
    Entity entity;
    char *text;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "is", textLabelSetTextKWList, &entity, &text)) {
        TextLabelComponent textLabelComponent = entityComponentOrchestrator->GetComponent<TextLabelComponent>(entity);
        textLabelComponent.text = std::string(text);
        entityComponentOrchestrator->UpdateComponent<TextLabelComponent>(entity, textLabelComponent);
        textRenderingEntitySystem->UpdateEntityText(entity, textLabelComponent);
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::text_label_get_color(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", nodeGetEntityKWList, &entity)) {
        TextLabelComponent textLabelComponent = entityComponentOrchestrator->GetComponent<TextLabelComponent>(entity);
        return Py_BuildValue("(ffff)", textLabelComponent.color.r, textLabelComponent.color.g, textLabelComponent.color.b, textLabelComponent.color.a);
    }
    return nullptr;
}

PyObject* PythonModules::text_label_set_color(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    float red, green, blue, alpha;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "iffff", nodeSetColorKWList, &entity, &red, &green, &blue, &alpha)) {
        TextLabelComponent textLabelComponent = entityComponentOrchestrator->GetComponent<TextLabelComponent>(entity);
        textLabelComponent.color = Color(red, green, blue, alpha);
        entityComponentOrchestrator->UpdateComponent<TextLabelComponent>(entity, textLabelComponent);
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::text_label_get_font(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", nodeGetEntityKWList, &entity)) {
        TextLabelComponent textLabelComponent = entityComponentOrchestrator->GetComponent<TextLabelComponent>(entity);
        Font *font = textLabelComponent.font;
        if (font == nullptr) {
            Py_RETURN_NONE;
        }
        return Py_BuildValue("(ssi)",
                             font->GetUID().c_str(),
                             font->GetFilePath().c_str(),
                             font->GetSize());
    }
    return nullptr;
}

PyObject* PythonModules::text_label_set_font(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    static AssetManager *assetManager = GD::GetContainer()->assetManager;
    Entity entity;
    char *pyUID;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "is", textLabelSetFontKWList, &entity, &pyUID)) {
        TextLabelComponent textLabelComponent = entityComponentOrchestrator->GetComponent<TextLabelComponent>(entity);
        textLabelComponent.font = assetManager->GetFont(std::string(pyUID));
        entityComponentOrchestrator->UpdateComponent<TextLabelComponent>(entity, textLabelComponent);
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::text_label_get_word_wrap(PyObject* self, PyObject* args, PyObject* kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", nodeGetEntityKWList, &entity)) {
        TextLabelComponent textLabelComponent = entityComponentOrchestrator->GetComponent<TextLabelComponent>(entity);
        if (textLabelComponent.wordWrap) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }
    return nullptr;
}

PyObject* PythonModules::text_label_set_word_wrap(PyObject* self, PyObject* args, PyObject* kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    bool wordWrap;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "ib", textLabelSetWordWrapKWList, &entity, &wordWrap)) {
        TextLabelComponent textLabelComponent = entityComponentOrchestrator->GetComponent<TextLabelComponent>(entity);
        textLabelComponent.wordWrap = wordWrap;
        entityComponentOrchestrator->UpdateComponent<TextLabelComponent>(entity, textLabelComponent);
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::text_label_get_max_characters_per_line(PyObject* self, PyObject* args, PyObject* kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", nodeGetEntityKWList, &entity)) {
        TextLabelComponent textLabelComponent = entityComponentOrchestrator->GetComponent<TextLabelComponent>(entity);
        return PyLong_FromUnsignedLong(textLabelComponent.maxCharactersPerLine);
    }
    return nullptr;
}

PyObject* PythonModules::text_label_set_max_characters_per_line(PyObject* self, PyObject* args, PyObject* kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    unsigned int maxCharacterPerLine;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "ii", textLabelSetMaxCharactersPerLineKWList, &entity, &maxCharacterPerLine)) {
        TextLabelComponent textLabelComponent = entityComponentOrchestrator->GetComponent<TextLabelComponent>(entity);
        textLabelComponent.maxCharactersPerLine = maxCharacterPerLine;
        entityComponentOrchestrator->UpdateComponent<TextLabelComponent>(entity, textLabelComponent);
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::text_label_get_new_line_padding(PyObject* self, PyObject* args, PyObject* kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", nodeGetEntityKWList, &entity)) {
        TextLabelComponent textLabelComponent = entityComponentOrchestrator->GetComponent<TextLabelComponent>(entity);
        return PyLong_FromLong(textLabelComponent.newLinePadding);
    }
    return nullptr;
}

PyObject* PythonModules::text_label_set_new_line_padding(PyObject* self, PyObject* args, PyObject* kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    unsigned int newLinePadding;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "ii", textLabelSetNewLinePaddingKWList, &entity, &newLinePadding)) {
        TextLabelComponent textLabelComponent = entityComponentOrchestrator->GetComponent<TextLabelComponent>(entity);
        textLabelComponent.newLinePadding = newLinePadding;
        entityComponentOrchestrator->UpdateComponent<TextLabelComponent>(entity, textLabelComponent);
        Py_RETURN_NONE;
    }
    return nullptr;
}

// COLLISION_SHAPE2D
PyObject* PythonModules::collision_shape2d_get_collider_rect(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", nodeGetEntityKWList, &entity)) {
        ColliderComponent colliderComponent = entityComponentOrchestrator->GetComponent<ColliderComponent>(entity);
        return Py_BuildValue("(ffff)", colliderComponent.collider.x, colliderComponent.collider.y, colliderComponent.collider.w, colliderComponent.collider.h);
    }
    return nullptr;
}

PyObject* PythonModules::collision_shape2d_set_collider_rect(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    float x, y, w, h;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "iffff", collisionShape2DSetColliderRectKWList, &entity, &x, &y, &w, &h)) {
        ColliderComponent colliderComponent = entityComponentOrchestrator->GetComponent<ColliderComponent>(entity);
        colliderComponent.collider = Rect2(x, y, w, h);
        entityComponentOrchestrator->UpdateComponent<ColliderComponent>(entity, colliderComponent);
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::collision_shape2d_add_collision_exception(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    Entity exceptionEntity;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "ii", collisionModifyCollisionExceptionKWList, &entity, &exceptionEntity)) {
        ColliderComponent colliderComponent = entityComponentOrchestrator->GetComponent<ColliderComponent>(entity);
        colliderComponent.collisionExceptions.emplace_back(exceptionEntity);
        entityComponentOrchestrator->UpdateComponent<ColliderComponent>(entity, colliderComponent);
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::collision_shape2d_remove_collision_exception(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    Entity exceptionEntity;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "ii", collisionModifyCollisionExceptionKWList, &entity, &exceptionEntity)) {
        ColliderComponent colliderComponent = entityComponentOrchestrator->GetComponent<ColliderComponent>(entity);
        colliderComponent.collisionExceptions.erase(std::remove(colliderComponent.collisionExceptions.begin(), colliderComponent.collisionExceptions.end(), exceptionEntity), colliderComponent.collisionExceptions.end());
        entityComponentOrchestrator->UpdateComponent<ColliderComponent>(entity, colliderComponent);
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::collision_shape2d_get_color(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", nodeGetEntityKWList, &entity)) {
        ColliderComponent colliderComponent = entityComponentOrchestrator->GetComponent<ColliderComponent>(entity);
        return Py_BuildValue("(ffff)", colliderComponent.color.r, colliderComponent.color.g, colliderComponent.color.b, colliderComponent.color.a);
    }
    return nullptr;
}

PyObject* PythonModules::collision_shape2d_set_color(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    Entity entity;
    float red, green, blue, alpha;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "iffff", nodeSetColorKWList, &entity, &red, &green, &blue, &alpha)) {
        ColliderComponent colliderComponent = entityComponentOrchestrator->GetComponent<ColliderComponent>(entity);
        colliderComponent.color = Color(red, green, blue, alpha);
        entityComponentOrchestrator->UpdateComponent<ColliderComponent>(entity, colliderComponent);
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::collision_shape2d_is_under_mouse(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    static CollisionEntitySystem *collisionEntitySystem = entityComponentOrchestrator->GetSystem<CollisionEntitySystem>();
    static MouseInput *mouseInput = MouseInput::GetInstance();
    Entity entity;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", nodeGetEntityKWList, &entity)) {
        if (collisionEntitySystem->IsEntityOnMouse(entity, mouseInput->GetMousePosition())) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }
    return nullptr;
}

// COLLISION
PyObject* PythonModules::collision_get_collided_nodes(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    static CollisionContext *collisionContext = GD::GetContainer()->collisionContext;
    static PythonCache *pythonCache = PythonCache::GetInstance();
    static ComponentManager *componentManager = GD::GetContainer()->componentManager;
    Entity entity;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", nodeGetEntityKWList, &entity)) {
        CPyObject pCollidedNodesList = PyList_New(0);
        pCollidedNodesList.AddRef();
        assert(pCollidedNodesList != nullptr && "node list empty!");
        for (Entity collidedEntity : collisionContext->GetEntitiesCollidedWith(entity)) {
            if (!entityComponentOrchestrator->IsEntityQueuedForDeletion(collidedEntity)) {
                if (pythonCache->HasActiveInstance(collidedEntity)) {
                    CPyObject &pCollidedClassInstance = pythonCache->GetClassInstance(collidedEntity);
                    pCollidedClassInstance.AddRef();
                    if (PyList_Append(pCollidedNodesList, pCollidedClassInstance) == -1) {
                        PyErr_Print();
                    }
                } else {
                    NodeComponent nodeComponent = componentManager->GetComponent<NodeComponent>(collidedEntity);
                    const std::string &nodeTypeString = NodeTypeHelper::GetNodeTypeString(nodeComponent.type);
                    if (PyList_Append(pCollidedNodesList, Py_BuildValue("(si)", nodeTypeString.c_str(), collidedEntity)) == -1) {
                        Logger::GetInstance()->Error("Error appending list");
                        PyErr_Print();
                    }
                }
            }
        }
        return pCollidedNodesList;
    }
    return nullptr;
}

PyObject* PythonModules::collision_get_collided_nodes_by_tag(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    static CollisionContext *collisionContext = GD::GetContainer()->collisionContext;
    static CollisionEntitySystem *collisionEntitySystem = entityComponentOrchestrator->GetSystem<CollisionEntitySystem>();
    static PythonCache *pythonCache = PythonCache::GetInstance();
    static ComponentManager *componentManager = GD::GetContainer()->componentManager;
    Entity entity;
    char *pyTag;
    float offsetX;
    float offsetY;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "isff", collisionGetCollidedNodesByTagKWList, &entity, &pyTag, &offsetX, &offsetY)) {
        collisionEntitySystem->ProcessEntityCollisionsByTag(entity, std::string(pyTag), Vector2(offsetX, offsetY));
        CPyObject pCollidedNodesList = PyList_New(0);
        pCollidedNodesList.AddRef();
        assert(pCollidedNodesList != nullptr && "node list empty!");
        for (Entity collidedEntity : collisionContext->GetEntitiesCollidedWith(entity)) {
            if (!entityComponentOrchestrator->IsEntityQueuedForDeletion(collidedEntity)) {
                if (pythonCache->HasActiveInstance(collidedEntity)) {
                    CPyObject &pCollidedClassInstance = pythonCache->GetClassInstance(collidedEntity);
                    pCollidedClassInstance.AddRef();
                    if (PyList_Append(pCollidedNodesList, pCollidedClassInstance) == -1) {
                        PyErr_Print();
                    }
                } else {
                    NodeComponent nodeComponent = componentManager->GetComponent<NodeComponent>(collidedEntity);
                    const std::string &nodeTypeString = NodeTypeHelper::GetNodeTypeString(nodeComponent.type);
                    if (PyList_Append(pCollidedNodesList, Py_BuildValue("(si)", nodeTypeString.c_str(), collidedEntity)) == -1) {
                        Logger::GetInstance()->Error("Error appending list");
                        PyErr_Print();
                    }
                }
            }
        }
        return pCollidedNodesList;
    }
    return nullptr;
}

PyObject* PythonModules::collision_update_collisions(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    static CollisionEntitySystem *collisionEntitySystem = entityComponentOrchestrator->GetSystem<CollisionEntitySystem>();
    Entity entity;
    float offsetX;
    float offsetY;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "iff", collisionUpdateCollisionsKWList, &entity, &offsetX, &offsetY)) {
        collisionEntitySystem->ProcessEntityCollisions(entity, Vector2(offsetX, offsetY));
    }

    Py_RETURN_NONE;
}

PyObject* PythonModules::collision_get_nodes_under_mouse(PyObject *self, PyObject *args) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    static CollisionEntitySystem *collisionEntitySystem = entityComponentOrchestrator->GetSystem<CollisionEntitySystem>();
    static PythonCache *pythonCache = PythonCache::GetInstance();
    static ComponentManager *componentManager = GD::GetContainer()->componentManager;
    static MouseInput *mouseInput = MouseInput::GetInstance();
    CPyObject pCollidedNodesList = PyList_New(0);
    pCollidedNodesList.AddRef();
    assert(pCollidedNodesList != nullptr && "node list empty!");
    for (Entity collidedEntity : collisionEntitySystem->GetEntitiesOnMouse(mouseInput->GetMousePosition())) {
        if (!entityComponentOrchestrator->IsEntityQueuedForDeletion(collidedEntity)) {
            if (pythonCache->HasActiveInstance(collidedEntity)) {
                CPyObject &pCollidedClassInstance = pythonCache->GetClassInstance(collidedEntity);
                pCollidedClassInstance.AddRef();
                if (PyList_Append(pCollidedNodesList, pCollidedClassInstance) == -1) {
                    Logger::GetInstance()->Error("Error appending to list with instance!");
                    PyErr_Print();
                }
            } else {
                NodeComponent nodeComponent = componentManager->GetComponent<NodeComponent>(collidedEntity);
                const std::string &nodeTypeString = NodeTypeHelper::GetNodeTypeString(nodeComponent.type);
                if (PyList_Append(pCollidedNodesList, Py_BuildValue("(si)", nodeTypeString.c_str(), collidedEntity)) == -1) {
                    Logger::GetInstance()->Error("Error appending to list without instance!");
                    PyErr_Print();
                }
                Logger::GetInstance()->Error("Error appending collision node (under mouse) to list, entity doesn't exist as a python instance!");
            }
        }
    }
    return pCollidedNodesList;
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

// MOUSE
PyObject* PythonModules::mouse_get_position(PyObject *self, PyObject *args) {
    static MouseInput *mouseInput = MouseInput::GetInstance();
    return Py_BuildValue("(ff)", mouseInput->GetMousePosition().x, mouseInput->GetMousePosition().y);
}

// SCENE
PyObject* PythonModules::scene_tree_change_scene(PyObject *self, PyObject *args, PyObject *kwargs) {
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    char *pyScenePath;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "s", sceneTreeChangeSceneKWList, &pyScenePath)) {
        entityComponentOrchestrator->PrepareSceneChange(std::string(pyScenePath));
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::scene_tree_get_current_scene_node(PyObject *self, PyObject *args) {
    static PythonCache *pythonCache = PythonCache::GetInstance();
    static SceneContext *sceneContext = GD::GetContainer()->sceneContext;
    static ComponentManager *componentManager = GD::GetContainer()->componentManager;
    if (pythonCache->HasActiveInstance(sceneContext->currentSceneEntity)) {
        CPyObject &pClassInstance = pythonCache->GetClassInstance(sceneContext->currentSceneEntity);
        pClassInstance.AddRef();
        return pClassInstance;
    }
    // Creates new instance on script side if active script instance of entity doesn't exist
    NodeComponent nodeComponent = componentManager->GetComponent<NodeComponent>(sceneContext->currentSceneEntity);
    const std::string &nodeTypeString = NodeTypeHelper::GetNodeTypeString(nodeComponent.type);
    return Py_BuildValue("(si)", nodeTypeString.c_str(), sceneContext->currentSceneEntity);
}

// NETWORK
PyObject* PythonModules::network_is_server(PyObject *self, PyObject *args) {
    static NetworkContext *networkContext = GD::GetContainer()->networkContext;
    if (networkContext->DoesServerExists()) {
        Py_RETURN_TRUE;
    }
    Py_RETURN_FALSE;
}

// SERVER
PyObject* PythonModules::server_start(PyObject *self, PyObject *args, PyObject *kwargs) {
    static NetworkContext *networkContext = GD::GetContainer()->networkContext;
    int port;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "i", serverStartKWList, &port)) {
        if (!networkContext->DoesServerExists()) {
            networkContext->CreateServer(port);
            networkContext->StartServer();
        }
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::server_stop(PyObject *self, PyObject *args) {
    static NetworkContext *networkContext = GD::GetContainer()->networkContext;
    if (networkContext->DoesServerExists()) {
        networkContext->RemoveServer();
    }
    Py_RETURN_NONE;
}

PyObject* PythonModules::server_send_message_to_all_clients(PyObject *self, PyObject *args, PyObject *kwargs) {
    static NetworkContext *networkContext = GD::GetContainer()->networkContext;
    char *pyMessage;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "s", networkSendMessageKWList, &pyMessage)) {
        networkContext->ServerSendMessageToAllClients(std::string(pyMessage));
        Py_RETURN_NONE;
    }
    return nullptr;
}

// CLIENT
PyObject* PythonModules::client_connect(PyObject *self, PyObject *args, PyObject *kwargs) {
    static NetworkContext *networkContext = GD::GetContainer()->networkContext;
    char *pyEndpoint;
    int port;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "si", clientConnectKWList, &pyEndpoint, &port)) {
        if (!networkContext->DoesClientExists()) {
            networkContext->CreateClient(std::string(pyEndpoint), port);
            networkContext->ConnectClient();
        }
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::client_disconnect(PyObject *self, PyObject *args) {
    static NetworkContext *networkContext = GD::GetContainer()->networkContext;
    if (networkContext->DoesClientExists()) {
        networkContext->RemoveClient();
    }
    Py_RETURN_NONE;
}

PyObject* PythonModules::client_send_message_to_server(PyObject *self, PyObject *args, PyObject *kwargs) {
    static NetworkContext *networkContext = GD::GetContainer()->networkContext;
    char *pyMessage;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "s", networkSendMessageKWList, &pyMessage)) {
        networkContext->ClientSendMessageToServer(std::string(pyMessage));
        Py_RETURN_NONE;
    }
    return nullptr;
}

// RENDERER
PyObject* PythonModules::renderer_draw_texture(PyObject *self, PyObject *args, PyObject *kwargs) {
    static Renderer2D *renderer = GD::GetContainer()->renderer2D;
    static AssetManager *assetManager = GD::GetContainer()->assetManager;
    char *pyTexturePath;
    float pySourceRectX;
    float pySourceRectY;
    float pySourceRectW;
    float pySourceRectH;
    float pyDestRectX;
    float pyDestRectY;
    float pyDestRectW;
    float pyDestRectH;
    int pyZIndex;
    float pyRotation;
    float pyColorRed;
    float pyColorGreen;
    float pyColorBlue;
    float pyColorAlpha;
    bool pyFlipX;
    bool pyFlipY;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "sffffffffifffffbb", rendererDrawTextureKWList,
                                    &pyTexturePath, &pySourceRectX, &pySourceRectY, &pySourceRectW, &pySourceRectH,
                                    &pyDestRectX, &pyDestRectY, &pyDestRectW, &pyDestRectH,
                                    &pyZIndex, &pyRotation, &pyColorRed, &pyColorGreen, &pyColorBlue, &pyColorAlpha,
                                    &pyFlipX, &pyFlipY)) {
        renderer->BatchDrawSprite(
            assetManager->GetTexture(std::string(pyTexturePath)),
            Rect2(pySourceRectX, pySourceRectY, pySourceRectW, pySourceRectH),
            Rect2(pyDestRectX, pyDestRectY, pyDestRectW, pyDestRectH),
            pyZIndex,
            pyRotation,
            Color(pyColorRed, pyColorGreen, pyColorBlue, pyColorAlpha),
            pyFlipX,
            pyFlipY
        );
        Py_RETURN_NONE;
    }
    return nullptr;
}

// TEXTURE
PyObject* PythonModules::texture_get(PyObject *self, PyObject *args, PyObject *kwargs) {
    static AssetManager *assetManager = GD::GetContainer()->assetManager;
    char *pyFilePath;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "s", textureGetKWList, &pyFilePath)) {
        const std::string &textureFilePath = std::string(pyFilePath);
        if (assetManager->HasTexture(textureFilePath)) {
            Texture *texture = assetManager->GetTexture(textureFilePath);
            return Py_BuildValue("(ssssii)",
                                 texture->GetWrapSString().c_str(),
                                 texture->GetWrapTString().c_str(),
                                 texture->GetFilterMinString().c_str(),
                                 texture->GetFilterMagString().c_str(),
                                 texture->GetWidth(),
                                 texture->GetHeight());
        }
        Logger::GetInstance()->Error("Invalid attempt at getting texture at path: " + textureFilePath);
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::texture_get_pixel_color(PyObject *self, PyObject *args, PyObject *kwargs) {
    static AssetManager *assetManager = GD::GetContainer()->assetManager;
    char *pyFilePath;
    int pixelX;
    int pixelY;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "sii", textureGetPixelColorKWList, &pyFilePath, &pixelX, &pixelY)) {
        const std::string &textureFilePath = std::string(pyFilePath);
        if (assetManager->HasTexture(textureFilePath)) {
            Texture *texture = assetManager->GetTexture(textureFilePath);
            Color color = texture->GetPixelColor(pixelX, pixelY);
            return Py_BuildValue("(ffff)",
                                 color.r,
                                 color.g,
                                 color.b,
                                 color.a);
        }
        Logger::GetInstance()->Error("Invalid attempt at getting texture pixel color at path: " + textureFilePath);
        Py_RETURN_NONE;
    }
    return nullptr;
}

// FONT
PyObject* PythonModules::font_create(PyObject *self, PyObject *args, PyObject *kwargs) {
    static AssetManager *assetManager = GD::GetContainer()->assetManager;
    char *pyUID;
    char *pyFilePath;
    int fontSize;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "ssi", fontCreateKWList, &pyUID, &pyFilePath, &fontSize)) {
        assetManager->LoadFont(std::string(pyUID), std::string(pyFilePath), fontSize);
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::font_get(PyObject *self, PyObject *args, PyObject *kwargs) {
    static AssetManager *assetManager = GD::GetContainer()->assetManager;
    char *pyUID;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "s", fontGetKWList, &pyUID)) {
        const std::string fontUID = std::string(pyUID);
        if (assetManager->HasFont(fontUID)) {
            Font *font = assetManager->GetFont(pyUID);
            return Py_BuildValue("(si)", font->GetFilePath().c_str(), font->GetSize());
        }
        Py_RETURN_NONE;
    }
    return nullptr;
}

// CONFIG TOOL
PyObject* PythonModules::config_tool_save_file(PyObject *self, PyObject *args, PyObject *kwargs) {
    ProjectProperties *projectProperties = ProjectProperties::GetInstance();
    char *pyFilePath;
    char *pyJsonData;
    char *pyEncryptionKey;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "sss", configToolSaveFileKWList, &pyFilePath, &pyJsonData, &pyEncryptionKey)) {
        const std::string &encryptionKey = std::string(pyEncryptionKey);
        if (!encryptionKey.empty()) {
            FileHelper::SaveGameDataEncrypted(std::string(pyFilePath), std::string(pyJsonData), projectProperties->gameTitle, encryptionKey);
        } else {
            FileHelper::SaveGameData(std::string(pyFilePath), std::string(pyJsonData), projectProperties->gameTitle);
        }
        Py_RETURN_NONE;
    }
    return nullptr;
}

PyObject* PythonModules::config_tool_load_file(PyObject *self, PyObject *args, PyObject *kwargs) {
    ProjectProperties *projectProperties = ProjectProperties::GetInstance();
    char *pyFilePath;
    char *pyEncryptionKey;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "ss", configToolLoadFileKWList, &pyFilePath, &pyEncryptionKey)) {
        const std::string &encryptionKey = std::string(pyEncryptionKey);
        std::string gameDataJson;
        if (!encryptionKey.empty()) {
            gameDataJson = FileHelper::LoadGameDataEncrypted(std::string(pyFilePath), projectProperties->gameTitle, encryptionKey);
        } else {
            gameDataJson = FileHelper::LoadGameData(std::string(pyFilePath), projectProperties->gameTitle);
        }
        return Py_BuildValue("s", gameDataJson.c_str());
    }
    return nullptr;
}

PyObject* PythonModules::config_tool_delete_file(PyObject *self, PyObject *args, PyObject *kwargs) {
    ProjectProperties *projectProperties = ProjectProperties::GetInstance();
    char *pyFilePath;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "s", configToolGetFileKWList, &pyFilePath)) {
        if (FileHelper::DeleteGameData(std::string(pyFilePath), projectProperties->gameTitle)) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }
    return nullptr;
}

PyObject* PythonModules::config_tool_does_file_exist(PyObject *self, PyObject *args, PyObject *kwargs) {
    ProjectProperties *projectProperties = ProjectProperties::GetInstance();
    char *pyFilePath;
    if (PyArg_ParseTupleAndKeywords(args, kwargs, "s", configToolGetFileKWList, &pyFilePath)) {
        if (FileHelper::DoesUserSaveFileExists(std::string(pyFilePath), projectProperties->gameTitle)) {
            Py_RETURN_TRUE;
        }
        Py_RETURN_FALSE;
    }
    return nullptr;
}
