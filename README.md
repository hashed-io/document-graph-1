# Document Graph data structure

This smart contract stores documents, which are comprised of lists of arbitrary data tagged within string->data maps.

Documents can be saved in a graph data structure, creating edges and vertices.  For example, one document may be a "member" (vertex) that has an edge (link) to another document for a "role".  

This contract uses "content addressing", meaning the key of the document is a hash of its contents.  Each hash must be unique in the table and this is enforced by the ```create``` action.

NOTE: currently, the graph supports bi-directional edges but I will likely remove this to align it to a Directed Acyclic Graph (DAG) like IPFS.

### Setup
NOTE: Assumes you have relevant environmnent setup..
``` bash
# use your key
KEY=EOS696y3uuryxgRRCiajXHBtiX9umXKvhBRGMygPa82HtQDrcDnE6
cleos create account eosio documents $KEY $KEY
cleos create account eosio bob $KEY $KEY
cleos create account eosio alice $KEY $KEY
cleos set contract documents document
```

You'll need to add the eosio.code permission (use your key)
``` bash
cleos push action eosio updateauth '{
    "account": "documents",
    "permission": "active",
    "parent": "owner",
    "auth": {
        "keys": [
            {
                "key": "EOS696y3uuryxgRRCiajXHBtiX9umXKvhBRGMygPa82HtQDrcDnE6",
                "weight": 1
            }
        ],
        "threshold": 1,
        "accounts": [
            {
                "permission": {
                    "actor": "documents",
                    "permission": "eosio.code"
                },
                "weight": 1
            }
        ],
        "waits": []
    }
}' -p documents@owner
```

## Javascript Quickstart
``` bash
cd js && yarn install && node index.js
```

#### Create a document from a file
``` bash
$ node index.js --file "../test/examples/each-type.json" --create --auth alice
Transaction Successfull :  7dc613a7c716897f498c95e5973333db5e6a9f5170f604cdcde1b4bb546bdef6
Documents table:  [
  {
    id: 0,
    hash: 'b0477c431b96fa65273cb8a5f60ffb1fd11a42cb05d6e19cf2d66300ad52b8c9',
    creator: 'alice',
    content: [ [Object], [Object], [Object], [Object], [Object], [Object] ],
    certificates: [],
    created_date: '2020-08-15T22:39:40.500',
    updated_date: '2020-08-15T22:39:40.500'
  }
]
```
NOTE: if you tried to recreate the same content a second time, it would fail to enforce in strict deduplication. This is similar to IPFS/IPLD specifications. There are more sample documents in the examples folder.

#### List documents
```
node index.js 
```
NOTE: use ```--json``` to show the entire document

#### Certify an existing document
```
node index.js --certify 526bbe0d21db98c692559db22a2a32fedbea378ca25a4822d52e1171941401b7 --auth bob
```

## cleos Quickstart
``` bash
# this content just illustrates the various types supported
cleos push action documents create '{
    "creator": "bob",
    "content": [
        {
            "key": "description",
            "value": [[
                "string",
                "loreum ipsum goes to the store, could also include markdown"
            ]]
        },
        {
            "key": "salary_amount",
            "value": [[
                "asset",
                "130.00 USD"
            ]]
        },
        {
            "key": "referrer",
            "value": [[
                "name",
                "friendacct"
            ]]
        },
        {
            "key": "vote_count",
            "value": [[
                "int64",
                67
            ]]
        },
        {
            "key": "reference_document",
            "value": [[
                "checksum256",
                "7b5755ce318c42fc750a754b4734282d1fad08e52c0de04762cb5f159a253c24"
            ]]
        },
        {
            "key": "milestones",
            "value": [[
                "time_point",
                "2020-08-15T16:01:54.000"
            ],
            [
                "time_point",
                "2020-08-19T16:01:54.000"
            ]]
        }
    ]
}' -p bob
```

Alice can fork the object. The content must be new or updated or else the action will fail and report back the hash. 
Only updated fields and the hash to the parent will be saved within a fork.
``` bash
cleos push action documents fork '{
    "hash": "",
    "creator": "alice",
    "content": [
        {
            "key": "salary_amount",
            "value": [[
                "asset",
                "150.00 USD"
            ]]
        }
    ]
}' -p alice
```


Any account can 'certify' a document, with notes.

``` bash
cleos push action documents certify '{
    "certifier": "documents",
    "hash": "b0477c431b96fa65273cb8a5f60ffb1fd11a42cb05d6e19cf2d66300ad52b8c9",
    "notes": "my certification notes"
}' -p documents
```


May need to add eosio.code permission
``` bash
cleos push action eosio updateauth '{
    "account": "documents",
    "permission": "active",
    "parent": "owner",
    "auth": {
        "keys": [
            {
                "key": "EOS696y3uuryxgRRCiajXHBtiX9umXKvhBRGMygPa82HtQDrcDnE6",
                "weight": 1
            }
        ],
        "threshold": 1,
        "accounts": [
            {
                "permission": {
                    "actor": "documents",
                    "permission": "eosio.code"
                },
                "weight": 1
            }
        ],
        "waits": []
    }
}' -p documents@owner
```