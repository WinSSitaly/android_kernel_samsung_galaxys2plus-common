
struct kvm_timer {
	struct hrtimer timer;
	s64 period; 				/* unit: ns */
<<<<<<< HEAD
	u32 timer_mode_mask;
	u64 tscdeadline;
=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	atomic_t pending;			/* accumulated triggered timers */
	bool reinject;
	struct kvm_timer_ops *t_ops;
	struct kvm *kvm;
	struct kvm_vcpu *vcpu;
};

struct kvm_timer_ops {
	bool (*is_periodic)(struct kvm_timer *);
};

enum hrtimer_restart kvm_timer_fn(struct hrtimer *data);
