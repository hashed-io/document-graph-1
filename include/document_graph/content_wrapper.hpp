#pragma once
#include <document_graph/content.hpp>

#include <string_view>

using std::string;
using std::string_view;

namespace hypha
{
    using ContentGroup = std::vector<Content>;
    using ContentGroups = std::vector<ContentGroup>;

    static const std::string CONTENT_GROUP_LABEL = std::string("content_group_label");

    class ContentWrapper
    {

    public:
        ContentWrapper(ContentGroups &cgs);
        ~ContentWrapper();

        // non-static definitions
        std::pair<int64_t, ContentGroup *> getGroup(const std::string &label);
        ContentGroup *getGroupOrFail(const std::string &label, const std::string &error);
        ContentGroup *getGroupOrFail(const std::string &groupLabel);

        std::pair<int64_t, Content *> get(const std::string &groupLabel, const std::string &contentLabel);
        //Looks for content in an specific group index
        std::pair<int64_t, Content *> get(size_t groupIndex, const std::string &contentLabel);
        Content *getOrFail(const std::string &groupLabel, const std::string &contentLabel, const std::string &error);
        Content *getOrFail(const std::string &groupLabel, const std::string &contentLabel);
        

        void removeGroup(const std::string &groupLabel);
        void removeGroup(size_t groupIndex);

        void removeContent(const std::string &groupLabel, const std::string &contentLabel);
        void removeContent(size_t groupIndex, const std::string &contentLabel);
        void removeContent(size_t groupIndex, size_t contentIndex);

        void insertOrReplace(size_t groupIndex, const Content &newContent);

        bool exists(const std::string &groupLabel, const std::string &contentLabel);

        static string_view getGroupLabel(const ContentGroup &contentGroup);
        static void insertOrReplace(ContentGroup &contentGroup, const Content &newContent);

    private:
        ContentGroups &getContentGroups() { return m_contentGroups; }
        ContentGroups &m_contentGroups;
    };

} // namespace hypha