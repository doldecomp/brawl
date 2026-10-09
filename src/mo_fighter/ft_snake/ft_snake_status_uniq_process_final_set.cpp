#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <ft/snake/ft_snake_status_uniq_process_final.h>
#include <ft/snake/ft_snake.h>
#include <cm/cm_controller_ai.h>
#include <mt/mt_vector.h>
#include <wn/snake/wn_snake_rgb6_sight.h>
#include <so/article/so_generate_article_manage_module.h>
#include <so/so_external_value_accesser.h>
#include <so/so_module_accesser.h>
#include <so/so_value_accesser.h>
#include <so/work/so_work_manage_module_impl.h>
extern cmAIController* g_cmAIController;
extern char lbl_122_data_78AC[], lbl_122_data_8554[];
extern "C" void* __dynamic_cast(void*, int, void*, void*, int);
ftSnakeStatusUniqProcessFinalSet g_ftSnakeStatusUniqProcessFinalSet;
ftSnakeStatusUniqProcessFinalSet::~ftSnakeStatusUniqProcessFinalSet() {}
void ftSnakeStatusUniqProcessFinalSet::execFixPos(soModuleAccesser* acc) {
    soGenerateArticleManageModule& articles = *static_cast<soGenerateArticleManageModule*>(
        acc->m_enumerationStart->m_generateArticleManageModule);
    soArticle* article = articles.getArticle(9);
    wnSnakeRgb6Sight* sight = static_cast<wnSnakeRgb6Sight*>(
        __dynamic_cast(article, 0, lbl_122_data_78AC, lbl_122_data_8554, 0));
    if (!sight) return;
    soWorkManageModule& work = acc->getWorkManageModule();
    if (work.isFlag(0x22000010)) {
        work.offFlag(0x22000010);
        sight->unableOperate();
    } else if (work.isFlag(0x22000011)) {
        work.offFlag(0x22000011);
        sight->enableOperate();
    }
    StageObject* object = static_cast<StageObject*>(sight);
    float cursorY = soExternalValueAccesser::getWorkFloat(object, 0x11000002);
    float cursorX = soExternalValueAccesser::getWorkFloat(object, 0x11000001);
    if (g_cmAIController) {
        char* viewport = reinterpret_cast<char*>(g_cmAIController);
        float width = (*reinterpret_cast<float*>(viewport + 0x170) -
                       *reinterpret_cast<float*>(viewport + 0x16C)) * 0.5f;
        float height = (*reinterpret_cast<float*>(viewport + 0x178) -
                        *reinterpret_cast<float*>(viewport + 0x174)) * 0.5f;
        cursorX /= width;
        cursorY /= height;
    }
    if (!g_cmAIController) return;
    soMotionModule& motion = acc->getMotionModule();
    int cameraKind = motion.getKind();
    if (cameraKind == 500) {
        float frameRate = (cursorY + 1.0f) * 0.5f;
        if (frameRate > 1.0f) frameRate = 1.0f;
        else if (frameRate < 0.0f) frameRate = 0.0f;
        float endFrame = motion.getEndFrame();
        float frame = motion.getFrame();
        float amount = soValueAccesser::getConstantFloat(acc, 0xFB4, 0);
        motion.setFrame(frame + (endFrame * frameRate - frame) * amount);
    }
    if (!work.isFlag(0x22000012)) {
        float x = work.getFloat(0x21000006);
        float rate;
        if (cameraKind == 0x1F5)
            rate = soValueAccesser::getConstantFloat(acc, 0xFB6, 0);
        else if (cameraKind == 0x1F6)
            rate = soValueAccesser::getConstantFloat(acc, 0xFB7, 0);
        else
            rate = soValueAccesser::getConstantFloat(acc, 0xFB5, 0);
        x += (cursorX - x) * rate;
        work.setFloat(x, 0x21000006);
        Vec2f cursor(x, 0.0f);
        ftSnake::syncFinalCursorRate(&cursor, acc);
    }
    ftSnakeStatusUniqProcessFinalCommon::setCameraOffsetZ(acc, 1.0f);
}
void ftSnakeStatusUniqProcessFinalSet::exitStatus(soModuleAccesser* acc, int next) {
    ftSnakeStatusUniqProcessFinalCommon::exitStatusCommon(acc, next);
}
