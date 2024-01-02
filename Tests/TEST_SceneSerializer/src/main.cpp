#include <gtest/gtest.h>
#include <Engine/ECS/SceneSerializer.h>

using namespace MyEngine;

// Fixture for SceneSerializer tests
class SceneSerializerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code, if any
        m_pScene = new Scene();
        m_pSerializer = new SceneSerializer(m_pScene);
    }

    void TearDown() override {
        // Teardown code, if any
        delete m_pSerializer;
        delete m_pScene;
    }

    // Member variables accessible to all tests
    Scene* m_pScene;
    SceneSerializer* m_pSerializer;
};

// Test serialization
TEST_F(SceneSerializerTest, SerializeTest) {
    const std::string filepath = "test_scene.json";

    // Perform serialization
    bool result = m_pSerializer->Serialize(filepath);

    // Check if serialization was successful
    EXPECT_TRUE(result);
}

// Test deserialization
TEST_F(SceneSerializerTest, DeserializeTest) {
    const std::string filepath = "test_scene.json";

    // Perform deserialization
    bool result = m_pSerializer->Deserialize(filepath);

    // Check if deserialization was successful
    EXPECT_TRUE(result);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
