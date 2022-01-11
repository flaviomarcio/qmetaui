import QtQuick 2.14

Item {
    id: control

    property string source: ''
    property var sourceComponent: undefined

    property Item form: getObject()

    property bool isLoaded: {
        var item=loader.item
        return (item!==undefined && item!==null)
    }

    signal show()
    signal close()

    signal load()
    signal loaded(var form)

    signal unload()
    signal unloaded()

    function getObject(){
        return loader.item
    }

    onLoad: { //NOTE DRIELE qual a diferença desse para o OPENFORM, F?
        if((control.sourceComponent !== undefined) && (control.sourceComponent !== null))
            loader.sourceComponent=control.sourceComponent
        else if(control.source!=='')
            loader.source = control.source
        else
            loader.free()
    }

    onUnload: {
        control.visible=false
        loader.free()
    }

    Loader {
        id: loader       

        function free(){
            // EXISTIA AQUI O TRATAMENTO DO  loader.source  AS STRING
            if((loader.sourceComponent !== null) || (loader.sourceComponent!==undefined) )
                loader.sourceComponent = undefined
        }

        onStatusChanged: {
            if(loader.status===Loader.Ready){
                control.visible = false
                form = loader.item
                form.parent = control.parent
                control.loaded(form)
            }
            else if(loader.status===Loader.Null){
                connection.target = null
                control.unloaded()
            }
        }

        Connections {
            id: connection
            target: null //NOTE DRIELE isso burla o warning por não ter o objeto setado
            function onShow(){
                control.show()
            }
            function onClose(){
                control.close()
            }
        }
    }
}


