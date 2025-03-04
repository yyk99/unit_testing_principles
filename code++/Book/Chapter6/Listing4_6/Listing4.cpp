//
// Book/Chapter6/Listing4_6/Listing4.cpp
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "DateTime.h"

class Comment
{
public:
    std::string Text;
    std::string Author;
    DateTime DateCreated;
public:
    Comment(std::string text, std::string author, DateTime dateCreated)
        : Text(text)
        , Author(author)
        , DateCreated(dateCreated)
    {
    }

public:
    bool operator == (Comment const& other) const
    {
        return Text == other.Text
            && Author == other.Author
            && DateCreated == other.DateCreated;
    }

};

class Article
{
private:
    std::vector<Comment> _comments; // = new List<Comment>();

public:
    std::vector<Comment> const& Comments() const { return _comments; }

    void AddComment(std::string text, std::string author, DateTime now)
    {
        _comments.push_back(Comment(text, author, now));
    }

    Article& ShouldContainNumberOfComments(int i)
    {
        return *this;
    }
};


class ArticleExtensions
{
};


class CustomerControllerTests : public testing::Test
{
public:
    static Article const& ShouldContainNumberOfComments(Article const& article, int commentCount)
    {
        // ASSERT_EQ(1, article.Comments.Count);
        if (commentCount != article.Comments().size())
            throw std::runtime_error("commentCount != article.Comments().size()");
        return article;
    }

    static Article const& WithComment(Article const& article, std::string text, std::string author, DateTime const& dateCreated)
    {
        //Comment comment = article.Comments.SingleOrDefault(x = > x.Text == text && x.Author == author && x.DateCreated == dateCreated);

        auto pos = std::find(article.Comments().begin(), article.Comments().end(), Comment(text, author, dateCreated));
        if (pos == article.Comments().end())
            throw std::runtime_error("pos == article.Comments().end()");
        // Assert.NotNull(comment);
        return article;
    }
};

// [Fact]
TEST_F(CustomerControllerTests, Adding_a_comment_to_an_article)
{
    auto sut = Article();
    std::string text = "Comment text";
    std::string author = "John Doe";
    auto now = DateTime(2019, 4, 1);

    sut.AddComment(text, author, now);

    ASSERT_EQ(1, sut.Comments().size());
    ASSERT_EQ(text, sut.Comments()[0].Text);
    ASSERT_EQ(author, sut.Comments()[0].Author);
    ASSERT_EQ(now, sut.Comments()[0].DateCreated);
};

// [Fact]
TEST_F(CustomerControllerTests, Adding_a_comment_to_an_article2)
{
    auto sut = Article();
    std::string text = "Comment text";
    std::string author = "John Doe";
    auto now = DateTime(2019, 4, 1);

    sut.AddComment(text, author, now);

    // sut.ShouldContainNumberOfComments(1)
    //     .WithComment(text, author, now);

    ASSERT_NO_THROW(
        WithComment(ShouldContainNumberOfComments(sut, 1),
            text, author, now)
    );
}

// [Fact]
TEST_F(CustomerControllerTests, Adding_a_comment_to_an_article3)
{
    auto sut = Article();
    auto comment = Comment(
        "Comment text",
        "John Doe",
        DateTime(2019, 4, 1));

    sut.AddComment(comment.Text, comment.Author, comment.DateCreated);

    // sut.Comments.Should()
    //     .BeEquivalentTo(comment);
}
