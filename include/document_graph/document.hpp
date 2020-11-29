#pragma once
#include <eosio/multi_index.hpp>
#include <variant>
#include <eosio/name.hpp>
#include <eosio/asset.hpp>
#include <eosio/transaction.hpp>
#include <eosio/crypto.hpp>

#include <document_graph/content.hpp>
#include <document_graph/content_group.hpp>

namespace hypha
{
    // unused for now, but leaving in the data structure for the future
    struct Certificate
    {
        Certificate() {}
        Certificate(const eosio::name &certifier, const std::string notes) : certifier{certifier}, notes{notes} {}

        eosio::name certifier;
        std::string notes;
        eosio::time_point certification_date = eosio::current_time_point();

        EOSLIB_SERIALIZE(Certificate, (certifier)(notes)(certification_date))
    };

    // TODO: need to move the contract ABI generator tag to a Macro
    struct [[eosio::table, eosio::contract("docs")]] Document
    {
    public:
        Document();

        // these constructors populate a Document instance without saving
        Document(eosio::name contract, eosio::name creator, ContentGroups contentGroups);
        Document(eosio::name contract, eosio::name creator, ContentGroup contentGroup);
        Document(eosio::name contract, eosio::name creator, Content content);
        Document(eosio::name contract, eosio::name creator, const std::string &label, const Content::FlexValue &value);

        // this constructor reads the hash from the table and populates the object from storage
        Document(eosio::name contract, const eosio::checksum256 &hash);
        ~Document();

        void emplace();

        static Document getOrNew(eosio::name contract, eosio::name creator, ContentGroups contentGroups);
        static Document getOrNew(eosio::name contract, eosio::name creator, ContentGroup contentGroup);
        static Document getOrNew(eosio::name contract, eosio::name creator, Content content);
        static Document getOrNew(eosio::name contract, eosio::name creator, const std::string &label, const Content::FlexValue &value);

        // certificates are not yet used
        void certify(const eosio::name &certifier, const std::string &notes);

        const void hashContents();

        // static version for use without creating an instance, useful for just checking a hash
        static const eosio::checksum256 hashContents(ContentGroups & contentGroups);
        static ContentGroups rollup(ContentGroup contentGroup);
        static ContentGroups rollup(Content content);

        const ContentGroups &getContentGroups() const { return content_groups; } // should this be const?
        const eosio::checksum256 &getHash() const { return hash; }
        const eosio::time_point &getCreated() const { return created_date; }
        const eosio::name &getCreator() const { return creator; }

    private:
        // members, with names as serialized - these must be public for EOSIO tables
        std::uint64_t id;
        eosio::checksum256 hash;
        eosio::name creator;
        ContentGroups content_groups;
        std::vector<Certificate> certificates;
        eosio::time_point created_date;
        eosio::name contract;

        // indexes for table
        uint64_t by_created() const { return created_date.sec_since_epoch(); }
        uint64_t by_creator() const { return creator.value; }
        eosio::checksum256 by_hash() const { return hash; }

        // toString iterates through all content, all levels, concatenating all values
        // the resulting string is used for fingerprinting and hashing
        const std::string toString();
        static const std::string toString(ContentGroups & contentGroups);
        static const std::string toString(ContentGroup & contentGroup);

        EOSLIB_SERIALIZE(Document, (id)(hash)(creator)(content_groups)(certificates)(created_date)(contract))

    public:
        // for unknown reason, primary_key() must be public
        uint64_t primary_key() const { return id; }

        typedef eosio::multi_index<eosio::name("documents"), Document,
                                   eosio::indexed_by<eosio::name("idhash"), eosio::const_mem_fun<Document, eosio::checksum256, &Document::by_hash>>,
                                   eosio::indexed_by<eosio::name("bycreator"), eosio::const_mem_fun<Document, uint64_t, &Document::by_creator>>,
                                   eosio::indexed_by<eosio::name("bycreated"), eosio::const_mem_fun<Document, uint64_t, &Document::by_created>>>
            document_table;
    };

} // namespace hypha