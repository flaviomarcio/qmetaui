import QtQuick 2.14

Item {
    id: control

    property string option_uuid
    property string option_url

    signal loaded()
    signal error()

    function option_path(){
        return "./"+option_uuid
    }

    function load(uuid){
        control.option_uuid=uuid
        pvt.make()
    }

    function clear(){
        control.option_uuid=""
        control.option_url=""
    }

    function jsonObject(){
        var jsonObject = pvt.option_json_source();
        return jsonObject;
    }

    Item {
        id: pvt

        property variant option_json_object: null
        function option_json_source(){
            var source ={
                'list':{
                    'form':{
                        'header':{
                             'title':'Lista de registros'
                            ,'columns':{
                                 '0':{'display':'Back'      ,'role':'back'   }
                                ,'1':{'display':'New'       ,'role':'new'    }
                                ,'2':{'display':'Edit'      ,'role':'edit'   }
                                ,'3':{'display':'Refresh'   ,'role':'refresh'}
                            }
                        }
                    }
                    ,'grid':{
                        'header':{
                             'title':'Form header edit'
                            ,'setting':{
                                  'column.height':'5%'
                                , 'column.width':'5%'
                                , 'row.height':'5%'
                                , 'row.width':'5%'
                                , 'horizontalAlignment': 'Text.AlignHCenter | Text.AlignLeft'
                                , 'verticalAlignment': 'Text.AlignVCenter'
                            }
                            ,'columns':{
                                 '0':{
                                      'display': 'Descrição'
                                    , 'role': 'desc'
                                    , 'width': '60%'
                                    , 'type': 'QVariant::String'
                                    , 'horizontalAlignment': 'Text.AlignHCenter | Text.AlignLeft'
                                    , 'verticalAlignment': 'Text.AlignVCenter'
                                }
                                ,'1':{
                                      'display': 'Quantidade'
                                    , 'role': 'qtd'
                                    , 'width': '20%'
                                    , 'type': 'QVariant::Double'
                                    , 'horizontalAlignment': 'Text.AlignHCenter | Text.AlignHRight'
                                    , 'verticalAlignment': 'Text.AlignVCenter'
                                }
                                ,'2':{
                                      'display': 'Ativo'
                                    , 'role': 'ativo'
                                    , 'width': '20%'
                                    , 'type': 'QVariant::Bool'
                                    , 'horizontalAlignment': 'Text.AlignHCenter'
                                    , 'verticalAlignment': 'Text.AlignVCenter'
                                }
                            }
                        }
                        ,'delegate':{
                            'component':{
                            }
                        }
                    }
                },
                'edit':{
                    'form':{
                        'header':{
                            'title':'Form header list'
                        },
                        'body':{
                        }
                    }
                }
            }

            var str=JSON.stringify(source)
            var json=JSON.parse(str)
            return json;
        }

        function make(){
            control.loaded()
        }
    }

    Component.onCompleted: {
        pvt.make()
    }
}
