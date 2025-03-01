#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include <vector>

class Message
{
public:
    std::string Header;
    std::string Body;
    std::string Footer;
};

class IRenderer
{
public:
    virtual std::string Render(Message const &message) = 0;
    virtual ~IRenderer() {}
};
class FooterRenderer : public IRenderer
{
public:
    std::string Render(Message const &message) override
    {
        return "<i>" + message.Footer + "</i>";
    }
};

class BodyRenderer : public IRenderer
{
public:
    std::string Render(Message const &message) override
    {
        return "<b>" + message.Body + "</b>";
    }
};

class HeaderRenderer : public IRenderer
{
public:
    std::string Render(Message const &message) override
    {
        return "<h1>" + message.Header + "</h1>";
    }
};

class MessageRenderer : public IRenderer
{
public:
    std::vector<IRenderer *> SubRenderers;

    MessageRenderer()
    : SubRenderers {
        new HeaderRenderer,
        new BodyRenderer,
        new FooterRenderer,
    }
    {
    }

    std::string Render(Message const &message) override
    {
        std::ostringstream ss;
        for (auto r : SubRenderers)
            ss << r->Render(message);
        return ss.str();
    }
};

class MessageRendererTests : public testing::Test {
};

// [Fact]
TEST_F(MessageRendererTests, Rendering_a_message)
{
    MessageRenderer sut;
    Message message
    {
        /*Header = */ "h",
        /*Body = */ "b",
        /*Footer = */ "f"
    };

    std::string html = sut.Render(message);

    ASSERT_EQ(std::string("<h1>h</h1><b>b</b><i>f</i>"), html);
}

// [Fact]
TEST_F(MessageRendererTests, MessageRenderer_uses_correct_sub_renderers)
{
    MessageRenderer sut;

    auto& renderers = sut.SubRenderers;

    ASSERT_EQ(3, renderers.size());
    // Assert.IsAssignableFrom<HeaderRenderer>(renderers[0]);
    // Assert.IsAssignableFrom<BodyRenderer>(renderers[1]);
    // Assert.IsAssignableFrom<FooterRenderer>(renderers[2]);
}

// [Fact(Skip = "Example of how not to write tests")]
TEST_F(MessageRendererTests, MessageRenderer_is_implemented_correctly)
{
    GTEST_SKIP() << "Example of how not to write tests";

//     std::string sourceCode = File.ReadAllText(@"<project path>\MessageRenderer.cs");

//             Assert.Equal(
//                 @"
// public class MessageRenderer : IRenderer
// {
//     public IReadOnlyList<IRenderer> SubRenderers { get; }

//     public MessageRenderer()
//     {
//         SubRenderers = new List<IRenderer>
//         {
//             new HeaderRenderer(),
//             new BodyRenderer(),
//             new FooterRenderer()
//         };
//     }

//     public string Render(Message message)
//     {
//         return SubRenderers
//             .Select(x => x.Render(message))
//             .Aggregate("", (str1, str2) => str1 + str2);
//     }
// }", sourceCode);
//         }
//     }
}

