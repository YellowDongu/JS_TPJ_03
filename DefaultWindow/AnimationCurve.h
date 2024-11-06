#pragma once
#include <cmath>
#define PI 3.141592f

// Easing �Լ��� �ð� �帧�� ���� �Ű������� ��ȭ���� �����մϴ�.
// ��κ��� ���� �繰���� ������ �ӵ��� �̵����� �ʰ�, ��� �����ϰų� ��� �������� �ʽ��ϴ�.
// ������ ���� ���ڸ�, ó������ ������ ���ٰ� ���� �� ������ ���뿡�� õõ�� ���ϴ�.
// �繰�� �ٴڿ� ����Ʈ���� ���� �繰�� �Ʒ��� �����ϴ� �繰�� �ٴ��� ���� �� ƨ�� �ö�ɴϴ�.
//
// 1. easeIn �迭 �Լ����� ���� ���ӵǴ� ȿ���� �����մϴ�.
// 2. easeOut �迭 �Լ����� �ݴ�� ���� ���ӵǴ� ȿ���� �����մϴ�.
// 3. easeInOut �迭 �Լ����� ���Ӱ� ������ ��� ����Ǿ� ���ʿ��� �ε巴�� ��ȯ�˴ϴ�.
// �� �Լ����� t�� 0���� 1���� ����Ǹ�, ������ ��� �����մϴ�. �ʿ信 �°� ����Ͻø� �˴ϴ�.
//	���� ��ũ : https://easings.net/ko

// ����
// a�� b���� �����̴µ� �ɸ��� �ð�(duration)�� �ִٰ��մϴ�.
// POINT StartPosition = a; // ������ ��ǥ
// POINT EndPosition   = b; // ������ ��ǥ
//
// float mCurrentTime = 0.f;
// float mDurationTime = 2.f; // a�� b���� �����̴µ� 2�ʰ� �ɸ���.
// void MoveAtoB()
//{
// 	 mCurrentTime += mDeltaTime;             // �����Ӵ� �ɸ��� �ð� �����ֱ�
//   float t = mCurrentTime / mDurationTime;
//   
//   a = Lerp(StartPosition, EndPosition, EaseInSine(t));
//}

struct AnimationCurve
{
    template<typename T>
    static T Lerp(T a, T b, float t) {
        return a + t * (b - a);
    }

    static float EaseInSine(float t)
	{
        return 1 - std::cos((t * PI) / 2);
    }

    static float EaseOutSine(float t) {
        return std::sin((t * PI) / 2);
    }

    static float EaseInOutSine(float t) {
        return -(std::cos(PI * t) - 1) / 2;
    }

    static float EaseInQuad(float t) {
        return t * t;
    }

    static float EaseOutQuad(float t) {
        return 1 - (1 - t) * (1 - t);
    }

    static float EaseInOutQuad(float t) {
        return t < 0.5f ? 2.f * t * t : 1.f - std::pow(-2.f * t + 2.f, 2.f) * 0.5f;
    }

    static float EaseInCubic(float t) {
        return t * t * t;
    }

    static float EaseOutCubic(float t) {
        return 1.f - std::pow(1.f - t, 3.f);
    }

    static float EaseInOutCubic(float t) {
        return t < 0.5 ? 4.f * t * t * t : 1.f - std::pow(-2.f * t + 2.f, 3.f) * 0.5f;
    }

    static float EaseInQuart(float t) {
        return t * t * t * t;
    }

    static float EaseOutQuart(float t) {
        return 1.f - std::pow(1.f - t, 4.f);
    }

    static float EaseInOutQuart(float t) {
        return t < 0.5 ? 8.f * t * t * t * t : 1.f - std::pow(-2.f * t + 2.f, 4.f) * 0.5f;
    }

    static float EaseInQuint(float t) {
        return t * t * t * t * t;
    }

    static float EaseOutQuint(float t) {
        return 1.f - std::pow(1.f - t, 5.f);
    }

    static float EaseInOutQuint(float t) {
        return t < 0.5 ? 16.f * t * t * t * t * t : 1.f - std::pow(-2.f * t + 2.f, 5.f) * 0.5f;
    }

    static float EaseInExpo(float t) {
        return t == 0 ? 0 : std::pow(2.f, 10.f * t - 10.f);
    }

    static float EaseOutExpo(float t) {
        return t == 1.f ? 1.f : 1.f - std::pow(2.f, -10.f * t);
    }

    static float EaseInOutExpo(float t) {
        if (t == 0) return 0;
        if (t == 1) return 1;
        return t < 0.5 ? std::pow(2.f, 20.f * t - 10.f) / 2.f : (2.f - std::pow(2.f, -20.f * t + 10.f)) * 0.5f;
    }

    static float EaseInCirc(float t) {
        return 1.f - std::sqrt(1.f - std::pow(t, 2.f));
    }

    static float EaseOutCirc(float t) {
        return std::sqrt(1.f - std::pow(t - 1.f, 2.f));
    }

    static float EaseInOutCirc(float t) {
        return t < 0.5f ? (1.f - std::sqrt(1.f - std::pow(2.f * t, 2.f))) / 2.f : (std::sqrt(1.f - std::pow(-2.f * t + 2.f, 2.f)) + 1.f) * 0.5f;
    }

    static float EaseInBack(float t) {
        const float c1 = 1.70158f;
        const float c3 = c1 + 1.f;
        return c3 * t * t * t - c1 * t * t;
    }

    static float EaseOutBack(float t) {
        const float c1 = 1.70158f;
        const float c3 = c1 + 1.f;
        return 1.f + c3 * std::pow(t - 1.f, 3.f) + c1 * std::pow(t - 1.f, 2.f);
    }

    static float EaseInOutBack(float t) {
        const float c1 = 1.70158f;
        const float c2 = c1 * 1.525f;
        return t < 0.5f
            ? (std::pow(2.f * t, 2.f) * ((c2 + 1.f) * 2.f * t - c2)) * 0.5f
            : (std::pow(2.f * t - 2.f, 2.f) * ((c2 + 1.f) * (t * 2.f - 2.f) + c2) + 2.f) * 0.5f;
    }

    static float EaseInElastic(float t) {
        const float c4 = (2.f * PI) / 3.f;
        return t == 0 ? 0 : t == 1.f ? 1.f : -std::pow(2.f, 10.f * t - 10.f) * std::sin((t * 10.f - 10.75f) * c4);
    }

    static float EaseOutElastic(float t) {
        const float c4 = (2.f * PI) / 3.f;
        return t == 0 ? 0 : t == 1.f ? 1.f : std::pow(2.f, -10.f * t) * std::sin((t * 10.f - 0.75f) * c4) + 1.f;
    }

    static float EaseInOutElastic(float t) {
        const float c5 = (2 * PI) / 4.5f;
        if (t == 0) return 0;
        if (t == 1.f) return 1.f;
        return t < 0.5f
            ? -(std::pow(2.f, 20.f * t - 10.f) * std::sin((20.f * t - 11.125f) * c5)) * 0.5f
            : (std::pow(2.f, -20.f * t + 10.f) * std::sin((20.f * t - 11.125f) * c5)) * 0.5f + 1;
    }

    static float EaseInBounce(float t) {
        return 1 - EaseOutBounce(1 - t);
    }

    static float EaseOutBounce(float t) {
        const float n1 = 7.5625f;
        const float d1 = 2.75f;

        if (t < 1 / d1) {
            return n1 * t * t;
        }
        else if (t < 2 / d1) {
            t -= 1.5f / d1;
            return n1 * t * t + 0.75f;
        }
        else if (t < 2.5 / d1) {
            t -= 2.25f / d1;
            return n1 * t * t + 0.9375f;
        }
        else {
            t -= 2.625f / d1;
            return n1 * t * t + 0.984375f;
        }
    }

    static float EaseInOutBounce(float t) {
        return t < 0.5f
            ? (1 - EaseOutBounce(1 - 2 * t)) * 0.5f
            : (1 + EaseOutBounce(2 * t - 1)) * 0.5f;
    }
};