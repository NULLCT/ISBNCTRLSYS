#include "ofMain.h"
#include "ofApp.h"
int main() {
  ofSetupOpenGL(1280, 720, OF_WINDOW);//OF_FULLSCREEN
  ofRunApp(new ofApp());
}
//�ȉ����I�ȃ���
//TODO:
/*
  -�Ƃ�܃��ō��B
  -�˗l�H���{�ɂ͊w�Z���s�̃o�[�R�[�h��\��炵��...
  ���e�Ƃ��Ă�9���̐������C���v�b�g�����炵���̂�int�^�Ɏ��܂�...?
  �ł�string,char�̂ق����Ǘ����₷���̂��B
  -���s���x�����R�Ƃ��čl������-�C���X�^���X���Ɏ��s�ɕ����Ԃ�������
  setting.addlanguage�����s���Ă���...
  �|�C���^�g����new Button�Ƃ����ăt�H���g�f�[�^��S�ẴC���X�^���X���Q�Ƃ���悤�ɏo���Ȃ���..?
  ������ˁB�A���[���Z�q�Ƃ��g���񂾂낤�Ȃ�...
  ���C���X�^���X���Ƃ�setup���Ȃ��Ƃ����Ȃ����烊�\�[�X���������͓̂�����O�Ȃ񂾂�Ȃ�....
  class����struct�ɕύX���܂�����
*/
//MEMO:
//�F
/*
#63FFD6 brue
#BBE85A green
#FFCB6F yellow
#E85A5E red
#AA87FF purpule
*/
//�ȉ��͉�ʍ\���Bscreen�ϐ��𑀍삷�邱�Ƃɂ���ĉ�ʐ؂�ւ�������B
//�ň��f�[�^��csv��M��...?
//portableVSCode�����Ă��悤
/*
seet 0:
  0:[�ψ��Ń��O�C��]1:[�Ǘ��Ń��O�C��]
seet 1:�ψ��Ń��O�C��
  2:[�{���p]
  3:[�{�ꗗ/����]
  4:[�g����]
  5:[�����������炱�̃{�^����������]6:[�e�L�X�g�{�b�N�X(�F�X������)]
seet 2:�{���p
  6:[ISBN�������ɓ��͂��āA�u�m��v�{�^���������Ă�������]
  7:[�N�[�|���Ȃ�E�̃`�F�b�N�{�b�N�X�������Ă�]8:[ ]
seet 3:�{�ꗗ/����
  [ISBNhogehoge]	[�����o�[]
  [ISBNhogehoge]  [�q�b�g�����{]
  [ISBNhogehoge]  [�ȉ��̖{�ɑ΂��Ă̑���]
  .
seet 4:�g����
  [����Ƃ��Đ����Ă������I]
seet 5:�����������炱�̃{�^�����������I
  [�G���[���e���X�}�z�ŎB���Đ}���ψ�LINE�ɑ��M���Ă��������B]
seet 6:�Ǘ��Ń��O�C��
  [Password:(syatiku)]
  9:[GodMode]
seet 7: GodMode
  [�C���X�g��]	10:[����]
  [ISBN]			[hogehoge]
 */

