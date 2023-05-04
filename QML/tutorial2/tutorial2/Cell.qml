import QtQuick

// Item は QML の最も基本的なビジュアル タイプであり、
// 他のタイプのコンテナとしてよく使用されます。
Item {
    id: container

    // プロパティcellColorを定義し,
    // rectangle.colorにバインディング
    property alias cellColor: rectangle.color

    signal clicked(cellColor: color)

    width: 40
    height: 25

    Rectangle {
        id: rectangle
        border.color: "white"
        anchors.fill: parent
    }

    MouseArea {
        anchors.fill: parent

        // MouseAreaがクリックされたらonClickedシグナルが飛ぶ.
        // container.clickedシグナルが飛ぶ.
        // シグナルにはcellColorを乗せる.
        onClicked: container.clicked(container.cellColor)
    }
}
