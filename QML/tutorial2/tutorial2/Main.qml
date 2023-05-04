import QtQuick

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

Rectangle {
    id: page // idを参照してオブジェクトにアクセスする
    width: parent.width
    height: parent.height
    color: "lightgray"

    Text {
        id: helloText
        text: qsTr("Hello world!")
        y: 30

        // parent.horizontalCenterでもOK
        anchors.horizontalCenter: page.horizontalCenter

        font.pointSize: 24
        font.bold: true
    }

    Grid {
        id: colorPicker
        x: 4 // 親からの相対x座標

        // https://doc.qt.io/qt-6/qtquick-positioning-anchors.html
        anchors.top: page.top
        anchors.topMargin: 4

//        anchors.bottom: page.bottom
//        anchors.bottomMargin: 4

        rows: 2
        columns: 3
        spacing: 10 // Cell間の間隔

        Cell {
            cellColor: "red"

            // onClickedシグナルに対するslotの定義
            // onSignalNameという名前のプロパティを介して,
            // Componentの任意のシグナルに反応できる.
            onClicked: helloText.color = cellColor
        }
        Cell {
            cellColor: "green"
            onClicked: helloText.color = cellColor
        }
        Cell {
            cellColor: "blue"
            onClicked: helloText.color = cellColor
        }
        Cell {
            cellColor: "yellow"
            onClicked: helloText.color = cellColor
        }
        Cell {
            cellColor: "steelblue"
            onClicked: helloText.color = cellColor
        }
        Cell {
            cellColor: "black"
            onClicked: helloText.color = cellColor
        }
    }
}
}
