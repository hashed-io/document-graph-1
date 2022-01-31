#pragma once

#include <cstring>

#include <eosio/eosio.hpp>
#include <eosio/asset.hpp>
#include <eosio/transaction.hpp>
#include <eosio/crypto.hpp>

#include <document_graph/document_graph.hpp>
#include <document_graph/hash_document.hpp>

using namespace eosio;

namespace hypha
{
   CONTRACT docs : public contract
   {

   public:
      docs(name self, name code, datastream<const char *> ds);
      ~docs();

      DECLARE_DOCUMENT_GRAPH(docs)

      // Any account/member can creator a new document
      ACTION create( eosio::name & creator, ContentGroups & content_groups );
      ACTION createdual (eosio::name &creator, ContentGroups &content_groups);

      ACTION createhash( eosio::name & creator, ContentGroups & content_groups );
      ACTION newhashdoc( eosio::name &creator);
      ACTION makehashdoc( eosio::name &creator, const eosio::checksum256& _hash);

   private:
      DocumentGraph m_dg = DocumentGraph(get_self());
   };
} // namespace hypha