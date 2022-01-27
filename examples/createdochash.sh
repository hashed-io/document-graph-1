cleos push action docs createhash '{"creator": "docs",
"content_groups": [
            [ 
                { "label": "content_group_label", "value": [ "string", "system" ] }, 
                { "label": "type", "value": [ "name", "farmer" ] }, 
                { "label": "node_label", "value": [ "string", "Familia Rodriguez Perez" ] } 
            ],
            [ 
                { "label": "content_group_label", "value": [ "string", "fixed_details" ] }, 
                { "label": "type", "value": [ "name", "document" ] }, 
                { "label": "owner", "value": [ "name", "tlaclocmant2" ] } 
            ], 
            [
                { "label": "content_group_label", "value": [ "string", "details" ] },
                { "label": "name", "value": [ "string", "Familia Rodriguez Perez" ] },
                { "label": "Founded", "value": [ "int64", "1983" ] }, 
                { "label": "Owners", "value": [ "string", "Pedro Rodrigues, Maria Perez" ] },
                { "label": "Region", "value": [ "string", "La Covnencion" ] },
                { "label": "Varaties", "value": [ "string", "Trinitario" ] },
                { "label": "Avg Yearly Tonage", "value": [ "int64", "5" ] },
                { "label": "BTC Address", "value": [ "string", "15ab8M9kEupfLLkct4fDMVxtiJgeAd4vxAA" ] },
                { "label": "Organic", "value": [ "string", "Yes" ] },
                { "label": "FairTrade", "value": [ "string", "No" ] },
                { "label": "Intro Video Youtube", "value": [ "string", "https://www.youtube.com/watch?v=4cNQ3xuv1yE" ] }
            ]
        ]

}' -p docs@active